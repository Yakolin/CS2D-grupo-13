#ifndef GAMES_MONITOR_H
#define GAMES_MONITOR_H

#include <mutex>
#include <map>

#include "game_loop.h"
#include <vector>
#include "player.h"

class GamesMonitor
{
private:
    std::mutex mutex;
    std::map<std::string, std::unique_ptr<GameLoop>> games;

public:
    GamesMonitor() = default;
    ~GamesMonitor() = default;

    void create_game(const std::string &game_name, const Player &player_creator);
    void join_game(const std::string &game_name, const Player &player_to_add);
    std::vector<std::string> list_games();
    void reap();
    void clear();
};

#endif // !GAMES_MONITOR_H
