#ifndef GAMES_MONITOR_H
#define GAMES_MONITOR_H

#include <mutex>
#include <map>

#include "game_loop.h"

class GamesMonitor
{
private:
    std::mutex mutex;
    std::map<std::string, std::unique_ptr<GameLoop>> games;

public:
    GamesMonitor() = default;
    ~GamesMonitor() = default;

    void create_game(const std::string &game_name);
    void join_game(const std::string &game_name, const std::string &player_name);

    void reap();
    void clear();
};

#endif // !GAMES_MONITOR_H
