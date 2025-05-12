#include "games_monitor.h"

GamesMonitor::GamesMonitor() = default;
GamesMonitor::~GamesMonitor() = default;

void GamesMonitor::create_game(const std::string &game_name)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (games.find(game_name) == games.end())
    {
        games[game_name] = std::make_unique<GameLoop>();
        games[game_name]->start();
    }
}

void GamesMonitor::join_game(const std::string &game_name, const std::string &player_name)
{
    std::lock_guard<std::mutex> lock(mutex);
    auto it = games.find(game_name);
    if (it != games.end())
    {
        it->second->add_player(player_name);
    }
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