#ifndef GAMES_MONITOR_H
#define GAMES_MONITOR_H

#include <map>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

#include "../../common/lobby_action.h"
#include "../interfaces/interface_games_monitor.h"

#include "game_loop.h"

class GamesMonitor: public InterfaceGamesMonitor {
private:
    std::mutex mutex;
    std::map<std::string, std::unique_ptr<GameLoop>> games;

public:
    GamesMonitor();
    ~GamesMonitor();

    bool create_game(player_id_t& player_id, const CreateGame& create_game,
                     std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                     std::shared_ptr<Queue<GameImage>>& send_queue, GameInfo& game_info) override;

    bool join_game(player_id_t& player_id, const JoinGame& join_game,
                   std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                   std::shared_ptr<Queue<GameImage>>& send_queue, GameInfo& game_info) override;

    std::vector<std::string> list_games() override;

    void reap();

    void clear();

    bool has_active_games();
};

#endif  // !GAMES_MONITOR_H
