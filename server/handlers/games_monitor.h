#ifndef GAMES_MONITOR_H
#define GAMES_MONITOR_H

#include <map>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

#include "game_loop.h"
#include "lobby_handler.h"

class LobbyHandler;
class GameLoop;

class InterfaceGamesMonitor {
public:
    InterfaceGamesMonitor() = default;
    virtual ~InterfaceGamesMonitor() = default;
    virtual void create_game(LobbyHandler& handler, const std::string& game_name) = 0;
    virtual void join_game(LobbyHandler& handler, const std::string& game_name) = 0;
    virtual void list_games(LobbyHandler& client_handler) = 0;
};


class GamesMonitor: public InterfaceGamesMonitor {
private:
    std::mutex mutex;
    std::map<std::string, std::unique_ptr<GameLoop>> games;

public:
    GamesMonitor();
    ~GamesMonitor();

    void create_game(LobbyHandler& client_handler, const std::string& game_name) override;
    void join_game(LobbyHandler& client_handler, const std::string& game_name) override;
    void list_games(LobbyHandler& client_handler) override;
    void reap();
    void clear();
};

#endif  // !GAMES_MONITOR_H
