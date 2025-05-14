#include <gtest/gtest.h>

#include "../server/protocol.h"
#include "mocks/mock_game.h"
#include "../common/socket.h"
#include <thread>

TEST(ServerProtocolTest, ReadPlayerCommandReturnCorrectType)
{
    // Arrange
    Socket server_socket("9999");

    std::thread client_thread([]()
                              {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<int32_t>(PlayerCommandType::MOVE_RIGHT);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command)); });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act
    PlayerCommandType result = protocol.read_player_command();

    // Assert
    EXPECT_EQ(result, PlayerCommandType::MOVE_RIGHT);

    client_thread.join();
}
