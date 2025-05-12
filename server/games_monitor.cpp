#include "games_monitor.h"

GamesMonitor::GamesMonitor() {}
GamesMonitor::~GamesMonitor() {}

bool GamesMonitor::create_game(const uint16_t &player_id, Socket &socket, const std::string &game_name)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (games.find(game_name) == games.end())
    {
        std::unique_ptr<GameLoop> game_loop = std::make_unique<GameLoop>(game_name);
        game_loop->add_player(player_id, socket);
        if (game_loop->is_full())
        {
            game_loop->start();
        }
        games[game_name] = std::move(game_loop);
        return true;
    }
    return false;
}

bool GamesMonitor::join_game(const uint16_t &player_id, Socket &socket, const std::string &game_name)
{
    std::lock_guard<std::mutex> lock(mutex);
    auto it = games.find(game_name);
    if (it != games.end())
    {
        it->second->add_player(player_id, socket);
        if (it->second->is_full())
        {
            it->second->start();
        }
        return true;
    }
    return false;
}

std::vector<std::string> GamesMonitor::list_games()
{
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<std::string> game_names;
    for (const auto &game : games)
    {
        game_names.push_back(game.first);
    }
    return game_names;
}

void GamesMonitor::reap()
{
    std::lock_guard<std::mutex> lock(mutex);
    auto it = games.begin();
    while (it != games.end())
    {
        if (!it->second->is_alive())
        {
            it->second->join();
            it = games.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void GamesMonitor::clear()
{
    std::lock_guard<std::mutex> lock(mutex);
    for (auto &game : games)
    {
        game.second->stop();
        game.second->join();
    }
    games.clear();
}