#ifndef MOCK_GAMES_MONITOR_H
#define MOCK_GAMES_MONITOR_H

#include <gmock/gmock.h>

#include "../../common/player_command_types.h"
#include "../../server/protocol/games_monitor.h"

class MockGamesMonitor: public InterfaceGamesMonitor {
public:
    MOCK_METHOD(bool, create_game, (const uint16_t& player_id, const std::string& game_name),
                (override));
    MOCK_METHOD(bool, join_game, (const uint16_t& player_id, const std::string& game_name),
                (override));
    MOCK_METHOD(std::vector<std::string>, list_games, (), (override));
};

#endif  // !MOCK_GAMES_MONITOR_H