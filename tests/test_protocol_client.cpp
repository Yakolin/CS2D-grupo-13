#include <memory>
#include <thread>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../client/model/client_action.h"
#include "../client/model/protocol.h"
#include "../common/lobby_types.h"
#include "../common/player_types.h"
#include "../common/socket.h"

using Client::BuyAmmo;
using Client::BuyWeapon;
using Client::CreateGame;
using Client::DefuseBomb;
using Client::DropBomb;
using Client::DropWeapon;
using Client::JoinGame;
using Client::ListGames;
using Client::Move;
using Client::PlantBomb;
using Client::Reload;
using Client::Shoot;

TEST(ClientProtocolTest, SendLobbyCommandSendCorrectType) {
    // Arrange
    Socket server_socket("9999");
    Socket skt("localhost", "9999");
    Socket accepted = server_socket.accept();
    ClientProtocol protocol(skt);
    lobby_command_t result;

    // Act
    protocol.send_lobby_command(LobbyCommandType::CREATE_GAME);

    // Assert
    accepted.recvall(&result, sizeof(result));
    EXPECT_EQ(static_cast<LobbyCommandType>(result), LobbyCommandType::CREATE_GAME);
}

TEST(ClientProtocolTest, SendPlayerCommandSendCorrectType) {
    // Arrange
    Socket server_socket("9999");
    Socket skt("localhost", "9999");
    Socket accepted = server_socket.accept();
    ClientProtocol protocol(skt);
    player_command_t result;

    // Act
    protocol.send_player_command(PlayerCommandType::MOVE);

    // Assert
    accepted.recvall(&result, sizeof(result));
    EXPECT_EQ(static_cast<PlayerCommandType>(result), PlayerCommandType::MOVE);
}

TEST(ClientProtocolTest, SendMoveSendCorrectObject) {
    // Arrange
    Socket server_socket("9999");
    Socket skt("localhost", "9999");
    Socket accepted = server_socket.accept();
    ClientProtocol protocol(skt);
    player_command_t command;
    move_t move_type;
    std::unique_ptr<InterfaceClientAction> action = std::make_unique<Move>(MoveType::RIGHT);

    // Act
    action->action(protocol);

    // Arrange
    accepted.recvall(&command, sizeof(command));
    EXPECT_EQ(static_cast<PlayerCommandType>(command), PlayerCommandType::MOVE);
    accepted.recvall(&move_type, sizeof(move_type));
    EXPECT_EQ(static_cast<MoveType>(move_type), MoveType::RIGHT);
}
