#include "game_loop.h"

GameLoop::GameLoop(const std::string& game_name):
        game_name(game_name),
        game(game_name, "pepito"),
        send_queues(),
        recv_queue(std::make_shared<Queue<std::unique_ptr<ClientAction>>>(QUEUE_MAX_SIZE)),
        constant_rate_loop([this]() { return this->should_keep_running(); },
                           [this]() { this->step(); }),
        game_started(false) {}

GameLoop::~GameLoop() {}

void GameLoop::add_player(player_id_t& player_id,
                          std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                          std::shared_ptr<Queue<GameImage>>& send_queue, GameInfo& game_info) {
    recv_queue = this->recv_queue;
    send_queues[player_id] = send_queue;
    this->game.add_player(player_id);
    game_info.walls = this->game.get_game_map();
}

bool GameLoop::is_full() { return (this->send_queues.size() == MAX_PLAYERS); }

bool GameLoop::waiting_for_players() { return !this->game_started; }

void GameLoop::run() {
    this->game_started = true;
    game.start_game();  // esto debe de llamarse posiblemente
    this->constant_rate_loop.execute();
}
void GameLoop::step() {
    try {
        std::unique_ptr<ClientAction> action = recv_queue->pop();
        game.process(*action);
        GameImage game_image = this->game.get_frame();
        this->broadcast(game_image);
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
            this->game.remove_player(player_id);
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
    try {
        this->recv_queue->close();
    } catch (const QueueAlreadyClosed& e) {}
    Thread::stop();
}
