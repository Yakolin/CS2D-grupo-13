#include <gtest/gtest.h>
#include "server/protocol.h"
#include "gmock/gmock.h"
#include "mocks/mock_socket.h"
#include "mocks/mock_game.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::WithArg;

TEST(ServerProtocolTest, ReadPlayerCommandReturnCorrectEnum)
{
    // Arrange
    MockSocket mock_socket("9999");
    ServerProtocol protocol(mock_socket);
    uint8_t rawCmd = static_cast<uint8_t>(PlayerCommandType::MOVE_RIGHT);

    // Act
    EXPECT_CALL(mock_socket, recvall(_, sizeof(rawCmd)))
        .WillOnce(
            DoAll(
                WithArg<0>([&](void *buf)
                           { *static_cast<uint8_t *>(buf) = rawCmd; }),
                Return() // recvall es void
                ));
    auto result = protocol.read_player_command();

    // Assert
    EXPECT_EQ(result, PlayerCommandType::MOVE_RIGHT);
}