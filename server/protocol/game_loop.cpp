#include "game_loop.h"
int contador = 0;
GameLoop::GameLoop(const std::string& game_name, const MapName& map_name):
        game_name(game_name),
        game(game_name, map_name),
        send_queues(),
        recv_queue(std::make_shared<Queue<std::unique_ptr<ClientAction>>>(QUEUE_MAX_SIZE)),
        players_ready(),
        constant_rate_loop([this]() { return this->should_keep_running(); },
                           [this]() { this->step(); }),
        max_players(read_max_players_from_config()),
        game_started(false) {}

GameLoop::~GameLoop() {}

max_players_t GameLoop::read_max_players_from_config(const std::string& path) {
    YAML::Node config = YAML::LoadFile(path);
    if (!config["max_players"]) {
        throw std::runtime_error("MAX_PLAYERS no está definido en el archivo YAML.");
    }
    return config["max_players"].as<max_players_t>();
}

void GameLoop::add_player(player_id_t& player_id, Skins& skins,
                          std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                          std::shared_ptr<Queue<GameImage>>& send_queue, GameInfo& game_info) {
    recv_queue = this->recv_queue;
    send_queues[player_id] = send_queue;
    players_ready[player_id] = false;
    this->game.add_player(player_id, skins);
    game_info = this->game.get_game_info();
}

bool GameLoop::is_full() { return (this->send_queues.size() == this->max_players); }

void GameLoop::player_ready(const player_id_t& player_id) {
    auto it = players_ready.find(player_id);
    if (it != players_ready.end()) {
        it->second = true;
        std::cout << "Jugador " << player_id << " está listo." << std::endl;
    } else {
        std::cerr << "Error: jugador " << player_id << " no encontrado." << std::endl;
    }
}

bool GameLoop::all_players_ready() {
    for (const auto& [player_id, ready]: players_ready) {
        if (!ready) {
            return false;
        }
    }
    return true;
}

bool GameLoop::waiting_for_players() { return !this->game_started; }

void GameLoop::end_game() {
    GameImage game_image = this->game.get_frame();
    game_image.game_state = GameStateImage(GameState::GAME_ENDED, 0, 0);
    this->game.stop_game();
    this->broadcast(
            game_image);  // solo habra un jugador y es el caso en el que no era single player
}

void GameLoop::run() {
    this->game_started = true;
    game.start_game();
    this->constant_rate_loop.execute();
}

void GameLoop::step() {
    if (!this->game.has_enough_players() && this->max_players != 1) {
        this->end_game();
    }

    if (!this->game.has_players() || this->game.has_ended()) {
        this->stop();
        return;
    }
    try {
        if (!this->game.has_ended()) {
            std::unique_ptr<ClientAction> action;
            while (this->recv_queue->try_pop(action)) {
                game.process(*action);
            }
            contador++;
            GameImage game_image = this->game.get_frame();
            this->broadcast(game_image);
        }
    } catch (const ClosedQueue& e) {
        this->stop();
    } catch (const std::runtime_error& e) {
        this->stop();
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Something went wrong in game_loop, and an unknown exception was caught."
                  << std::endl;
        this->stop();
    }
}


void GameLoop::broadcast(GameImage& game_image) {
    std::vector<player_id_t> to_remove;

    for (auto& [player_id, send_queue]: send_queues) {
        if (!send_queue) {
            to_remove.push_back(player_id);
            continue;
        }
        try {
            send_queue->push(game_image);
        } catch (const ClosedQueue& e) {
            std::cerr << "Info: una send_queue está cerrada, se eliminará del juego.\n";
            to_remove.push_back(player_id);
        } catch (const std::exception& e) {
            std::cerr << "Error inesperado al enviar por send_queue: " << e.what() << "\n";
        }
    }

    for (const auto& player_id: to_remove) {
        this->game.remove_player(player_id);
        send_queues.erase(player_id);
    }
}

void GameLoop::stop() {
    this->recv_queue->close();
    Thread::stop();
}
