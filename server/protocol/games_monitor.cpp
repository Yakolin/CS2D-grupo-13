#include "games_monitor.h"

GamesMonitor::GamesMonitor() {}
GamesMonitor::~GamesMonitor() {}

bool GamesMonitor::create_game(player_id_t& player_id, const std::string& game_name,
                               std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                               std::shared_ptr<Queue<GameImage>>& send_queue) {
    std::lock_guard<std::mutex> lock(mutex);
    if (games.find(game_name) == games.end()) {
        std::unique_ptr<GameLoop> game_loop = std::make_unique<GameLoop>(game_name);
        game_loop->add_player(player_id, recv_queue, send_queue);
        if (game_loop->is_full()) {
            game_loop->start();
        }
        games[game_name] = std::move(game_loop);
        std::cout << "Partida creada" << game_name << std::endl;
        return true;
    }
    return false;
}

bool GamesMonitor::join_game(player_id_t& player_id, const std::string& game_name,
                             std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                             std::shared_ptr<Queue<GameImage>>& send_queue) {
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Me uno a la partida" << player_id << std::endl;
    auto it = games.find(game_name);
    if (it != games.end()) {
        if (!it->second->is_full()) {
            it->second->add_player(player_id, recv_queue, send_queue);
            if (it->second->is_full()) {
                std::cout << "Comienza la partida" << player_id << std::endl;
                it->second->start();
            }
            return true;
        }
    }
    return false;
}

std::vector<std::string> GamesMonitor::list_games() {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<std::string> game_names;
    for (const auto& game: games) {
        game_names.push_back(game.first);
    }
    return game_names;
}

void GamesMonitor::reap() {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = games.begin();
    while (it != games.end()) {
        if (!it->second->waiting_for_players()) {
            if (!it->second->is_alive()) {
                it->second->join();
                it = games.erase(it);
            }
        } else {
            ++it;
        }
    }
    std::cout << "No hay problemas en el monitor" << std::endl;
}

void GamesMonitor::clear() {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& game: games) {
        std::cout << "Stop game" << std::endl;
        game.second->stop();
        game.second->join();
    }
    games.clear();
}