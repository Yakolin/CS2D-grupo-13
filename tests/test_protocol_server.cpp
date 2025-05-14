#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../server/protocol.h"
#include "mocks/mock_game.h"
#include "../common/socket.h"
#include <thread>
#include <memory>

TEST(ServerProtocolTest, ReadPlayerCommandReturnCorrectType)
{
    // Arrange
    Socket server_socket("9999");

    std::thread client_thread([]()
                              {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::MOVE);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command)); });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act
    PlayerCommandType result = protocol.read_player_command();

    // Assert
    EXPECT_EQ(result, PlayerCommandType::MOVE);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadMoveRightReturnCorrectObject)
{
    // Arrange
    MockGame mock_game;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]()
                              {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::MOVE);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command)); 
        move_t move_type = static_cast<move_t>(MoveType::RIGHT); 
        client_socket.sendall(reinterpret_cast<char*>(&move_type), sizeof(move_type)); });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<PlayerAction> action = protocol.read_move(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::MOVE);
    EXPECT_CALL(mock_game, move(player_id, MoveType::RIGHT))
        .Times(1);

    // Ejecutamos la acción “inyectando” nuestro mock
    action->action(mock_game);

    client_thread.join();
}
