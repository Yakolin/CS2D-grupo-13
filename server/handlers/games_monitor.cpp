#include "games_monitor.h"

GamesMonitor::GamesMonitor() {}
GamesMonitor::~GamesMonitor() {}

void GamesMonitor::create_game(LobbyHandler& client_creator, const std::string& game_name) {
    std::lock_guard<std::mutex> lock(mutex);
    if (games.find(game_name) == games.end()) {
        std::unique_ptr<GameLoop> game_loop = std::make_unique<GameLoop>(client_creator, game_name);
        if (game_loop->is_full()) {
            game_loop->start();
        }
        games[game_name] = std::move(game_loop);
    }
}

void GamesMonitor::join_game(LobbyHandler& lobby_handler, const std::string& game_name) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = games.find(game_name);
    if (it != games.end()) {
        it->second->add_player(lobby_handler);
        if (it->second->is_full()) {
            it->second->start();
        }
    }
}

void GamesMonitor::list_games(LobbyHandler& lobby_handler) {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<std::string> game_names;
    for (const auto& game: games) {
        game_names.push_back(game.first);
    }
    lobby_handler.send_list_games(game_names);
}

void GamesMonitor::reap() {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = games.begin();
    while (it != games.end()) {
        if (!it->second->is_alive()) {
            it->second->join();
            it = games.erase(it);
        } else {
            ++it;
        }
    }
}

void GamesMonitor::clear() {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& game: games) {
        game.second->stop();
        game.second->join();
    }
    games.clear();
}