#include <memory>
#include <thread>

#include <arpa/inet.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../client/model/client_action.h"
#include "../../client/model/protocol.h"
#include "../../common/lobby_types.h"
#include "../../common/player_command_types.h"
#include "../../common/socket.h"

using ClientSpace::BuyAmmo;
using ClientSpace::BuyWeapon;
using ClientSpace::CreateGame;
using ClientSpace::DefuseBomb;
using ClientSpace::Drop;
using ClientSpace::Equip;
using ClientSpace::JoinGame;
using ClientSpace::ListGames;
using ClientSpace::Move;
using ClientSpace::PlantBomb;
using ClientSpace::Reload;
using ClientSpace::Shoot;

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

TEST(ClientProtocolTest, SendCreateGameSendCorrectObject) {
    // Arrange
    Socket server_listener("9999");
    Socket client("localhost", "9999");
    Socket accepted = server_listener.accept();
    ClientProtocol protocol(client);
    std::string game_name = "test_game";

    // Act
    protocol.send_create_game(game_name);

    // Assert
    uint8_t header;
    accepted.recvall(&header, sizeof(header));
    EXPECT_EQ(static_cast<LobbyCommandType>(header), LobbyCommandType::CREATE_GAME);

    uint16_t net_len;
    accepted.recvall(&net_len, sizeof(net_len));
    uint16_t len = ntohs(net_len);
    EXPECT_EQ(len, game_name.size());

    std::string buf(len, '\0');
    accepted.recvall(&buf[0], len);
    EXPECT_EQ(buf, game_name);
}

TEST(ClientProtocolTest, SendJoinGameSendCorrectObject) {
    // Arrange
    Socket server_listener("9999");
    Socket client("localhost", "9999");
    Socket accepted = server_listener.accept();
    ClientProtocol protocol(client);
    std::string game_name = "join_test";

    // Act
    protocol.send_join_game(game_name);

    // Assert
    uint8_t header;
    accepted.recvall(&header, sizeof(header));
    EXPECT_EQ(static_cast<LobbyCommandType>(header), LobbyCommandType::JOIN_GAME);

    uint16_t net_len;
    accepted.recvall(&net_len, sizeof(net_len));
    uint16_t len = ntohs(net_len);
    EXPECT_EQ(len, game_name.size());

    std::string buf(len, '\0');
    accepted.recvall(&buf[0], len);
    EXPECT_EQ(buf, game_name);
}

TEST(ClientProtocolTest, SendListGamesSendCorrectObject) {
    // Arrange
    Socket server_listener("9999");
    Socket client("localhost", "9999");
    Socket accepted = server_listener.accept();
    ClientProtocol protocol(client);

    // Act
    protocol.send_list_games();

    // Assert
    uint8_t header;
    accepted.recvall(&header, sizeof(header));
    EXPECT_EQ(static_cast<LobbyCommandType>(header), LobbyCommandType::LIST_GAMES);
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