#ifndef MOCK_GAMES_MONITOR_H
#define MOCK_GAMES_MONITOR_H

#include <memory>
#include <string>
#include <vector>

#include <gmock/gmock.h>

#include "../../common/lobby_action.h"
#include "../../common/player_command_types.h"
#include "../../server/protocol/games_monitor.h"

class MockGamesMonitor: public InterfaceGamesMonitor {
public:
    MOCK_METHOD(bool, create_game,
                (player_id_t & player_id, const CreateGame& create_game,
                 std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                 std::shared_ptr<Queue<GameImage>>& send_queue, GameInfo& game_info),
                (override));

    MOCK_METHOD(bool, join_game,
                (player_id_t & player_id, const JoinGame& join_game,
                 std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                 std::shared_ptr<Queue<GameImage>>& send_queue, GameInfo& game_info),
                (override));

    MOCK_METHOD(std::vector<std::string>, list_games, (), (override));
};

#endif  // !MOCK_GAMES_MONITOR_H
