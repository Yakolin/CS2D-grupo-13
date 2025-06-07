#ifndef INTERFACE_GAMES_MONITOR_H
#define INTERFACE_GAMES_MONITOR_H

#include <memory>
#include <string>
#include <vector>

#include "../../common/game_image.h"
#include "../../common/game_info.h"
#include "../../common/lobby_action.h"
#include "../../common/player_command_types.h"
#include "../../common/queue.h"

class ClientAction;

class InterfaceGamesMonitor {
public:
    InterfaceGamesMonitor() = default;
    virtual ~InterfaceGamesMonitor() = default;
    virtual bool create_game(player_id_t& player_id, const CreateGame& create_game,
                             std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                             std::shared_ptr<Queue<GameImage>>& send_queue,
                             GameInfo& game_info) = 0;
    virtual bool join_game(player_id_t& player_id, const JoinGame& join_game,
                           std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                           std::shared_ptr<Queue<GameImage>>& send_queue, GameInfo& game_info) = 0;
    virtual std::vector<std::string> list_games() = 0;
};


#endif  // !INTERFACE_GAMES_MONITOR_H