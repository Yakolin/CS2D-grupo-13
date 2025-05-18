#ifndef GAMES_MONITOR_H
#define GAMES_MONITOR_H

#include <map>
#include <mutex>
#include <utility>
#include <vector>

#include "game_loop.h"
#include "player.h"


class InterfaceGamesMonitor {
public:
    InterfaceGamesMonitor() = default;
    virtual ~InterfaceGamesMonitor() = default;
    virtual bool create_game(const uint16_t& player_id, const std::string& game_name) = 0;
    virtual bool join_game(const uint16_t& player_id, const std::string& game_name) = 0;
    virtual std::vector<std::string> list_games() = 0;
};


class GamesMonitor: public InterfaceGamesMonitor {
private:
    std::mutex mutex;
    std::map<std::string, std::unique_ptr<GameLoop>> games;

public:
    GamesMonitor();
    ~GamesMonitor();

    bool create_game(const uint16_t& player_id, Socket& socket, const std::string& game_name);
    bool join_game(const uint16_t& player_id, Socket& socket, const std::string& game_name);
    std::vector<std::string> list_games();
    void reap();
    void clear();
};

#endif  // !GAMES_MONITOR_H
