#ifndef GAMES_MONITOR_H
#define GAMES_MONITOR_H

#include <map>
#include <mutex>
#include <utility>
#include <vector>

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

public:
    GamesMonitor() = default;
    ~GamesMonitor() = default;
};

#endif  // !GAMES_MONITOR_H