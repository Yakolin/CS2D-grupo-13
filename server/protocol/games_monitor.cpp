#include "games_monitor.h"

GamesMonitor::GamesMonitor() {}
GamesMonitor::~GamesMonitor() {}

bool GamesMonitor::create_game(player_id_t& player_id, const CreateGame& create_game,
                               std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                               std::shared_ptr<Queue<GameImage>>& send_queue, GameInfo& game_info) {
    std::lock_guard<std::mutex> lock(mutex);
    std::string game_name = create_game.game_name;
    MapName map_name = create_game.map_name;
    Skins skins = create_game.skins;
    if (games.find(game_name) == games.end()) {
        std::unique_ptr<GameLoop> game_loop =
                std::make_unique<GameLoop>(create_game.game_name, map_name);
        game_loop->add_player(player_id, skins, recv_queue, send_queue, game_info);
        games[game_name] = std::move(game_loop);
        std::cout << "Partida creada" << game_name << std::endl;
        return true;
    }
    return false;
}

bool GamesMonitor::join_game(player_id_t& player_id, const JoinGame& join_game,
                             std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                             std::shared_ptr<Queue<GameImage>>& send_queue, GameInfo& game_info) {
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Me uno a la partida" << player_id << std::endl;
    auto it = games.find(join_game.game_name);
    if (it != games.end()) {
        if (!it->second->is_full()) {
            Skins skins = join_game.skins;
            it->second->add_player(player_id, skins, recv_queue, send_queue, game_info);
            return true;
        }
    }
    return false;
}

std::vector<std::string> GamesMonitor::list_games() {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<std::string> game_names;
    for (const auto& game: games) {
        if (!game.second->is_full())
            game_names.push_back(game.first);
    }
    return game_names;
}

void GamesMonitor::player_ready(player_id_t& player_id, const std::string& game_name) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = games.find(game_name);
    if (it != games.end()) {
        it->second->player_ready(player_id);
        if (it->second->all_players_ready() && it->second->is_full()) {
            it->second->start();
        }
    } else {
        std::cout << "No existe la partida: " << game_name << std::endl;
    }
}

void GamesMonitor::reap() {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = games.begin();
    while (it != games.end()) {
        // si no estoy esperando por jugadores significa que la partida comenzo
        if (!it->second->waiting_for_players()) {
            if (!it->second->is_alive()) {
                it->second->join();
                it = games.erase(it);
                continue;
            }
        }
        ++it;
    }
}

void GamesMonitor::clear() {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& game: games) {
        std::cout << "Shutdown game..." << std::endl;
        game.second->stop();

        // es un hilo aun no inicializado si devuelve true, si devuelve false es una partida que
        // empezo, no puedo joinear hilos no inicializados
        if (!game.second->waiting_for_players()) {
            game.second->join();
        }
    }
    games.clear();
}

bool GamesMonitor::has_active_games() {
    std::lock_guard<std::mutex> lock(mutex);
    return !this->games.empty();
}