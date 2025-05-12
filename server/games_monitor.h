#ifndef GAMES_MONITOR_H
#define GAMES_MONITOR_H

#include <mutex>
#include <map>

#include "game_loop.h"
#include <vector>
#include "player.h"
#include <utility>

class GamesMonitor
{
private:
    std::mutex mutex;
    std::map<std::string, std::unique_ptr<GameLoop>> games;

public:
    GamesMonitor() = default;
    ~GamesMonitor() = default;

    void create_game(const uint16_t &player_id, Socket &socket, const std::string &game_name, const uint16_t &number_of_players);
    void join_game(const uint16_t &player_id, Socket &socket, const std::string &game_name);
    std::vector<std::string> list_games();
    void reap();
    void clear();
};

#endif // !GAMES_MONITOR_H
