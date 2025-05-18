#include <memory>
#include <thread>

#include <arpa/inet.h>
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
using Client::Drop;
using Client::Equip;
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

TEST(ClientProtocolTest, ReadPlayerIdReturnsCorrectId) {
    // Arrange
    Socket server_listener("9999");
    Socket client("localhost", "9999");
    Socket accepted = server_listener.accept();
    ClientProtocol protocol(client);

    uint8_t handshake_byte = static_cast<uint8_t>(HandshakeType::HANDSHAKE);
    player_id_t expected_id = 456;
    uint16_t net_id = htons(expected_id);

    accepted.sendall(&handshake_byte, sizeof(handshake_byte));
    accepted.sendall(&net_id, sizeof(net_id));

    // Act
    player_id_t result = protocol.read_player_id();

    // Assert
    EXPECT_EQ(result, expected_id);
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
