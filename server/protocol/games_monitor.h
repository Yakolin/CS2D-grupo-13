#ifndef GAMES_MONITOR_H
#define GAMES_MONITOR_H

#include <map>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

#include "../interfaces/interface_games_monitor.h"

#include "game_loop.h"

class GamesMonitor: public InterfaceGamesMonitor {
private:
    std::mutex mutex;
    std::map<std::string, std::unique_ptr<GameLoop>> games;

public:
    GamesMonitor();
    ~GamesMonitor();

    bool create_game(player_id_t player_id, const std::string& game_name,
                     std::shared_ptr<Queue<std::unique_ptr<IActionToPlayer>>>& recv_queue,
                     std::shared_ptr<Queue<GameImage>>& send_queue) override;

    bool join_game(player_id_t player_id, const std::string& game_name,
                   std::shared_ptr<Queue<std::unique_ptr<IActionToPlayer>>>& recv_queue,
                   std::shared_ptr<Queue<GameImage>>& send_queue) override;

    std::vector<std::string> list_games() override;

    void reap();

    void clear();
};

#endif  // !GAMES_MONITOR_H
