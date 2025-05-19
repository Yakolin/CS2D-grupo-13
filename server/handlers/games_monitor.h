#ifndef GAMES_MONITOR_H
#define GAMES_MONITOR_H

#include <map>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

#include "../client_handler/handler.h"
#include "../protocol/client_action.h"

#include "game_loop.h"

class InterfaceGamesMonitor {
public:
    InterfaceGamesMonitor() = default;
    virtual ~InterfaceGamesMonitor() = default;
    virtual void create_game(const player_id_t player_id, ClientHandler& client_handler,
                             const std::string& game_name) = 0;
    virtual void join_game(const player_id_t player_id, ClientHandler& client_handler,
                           const std::string& game_name) = 0;
    virtual void list_games(ClientHandler& client_handler) = 0;
};


class GamesMonitor: public InterfaceGamesMonitor {
private:
    std::mutex mutex;
    std::map<std::string, std::unique_ptr<GameLoop>> games;

public:
    GamesMonitor();
    ~GamesMonitor();

    void create_game(const player_id_t player_id, ClientHandler& client_handler,
                     const std::string& game_name);
    void join_game(const player_id_t player_id, ClientHandler& client_handler,
                   const std::string& game_name);
    void list_games(ClientHandler& client_handler);
    void reap();
    void clear();
};

#endif  // !GAMES_MONITOR_H
