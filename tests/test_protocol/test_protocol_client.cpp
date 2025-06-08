#include <memory>
#include <thread>

#include <arpa/inet.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../client/model/client_action.h"
#include "../../client/model/protocol.h"
#include "../../common/lobby_action.h"
#include "../../common/lobby_types.h"
#include "../../common/player_command_types.h"
#include "../../common/socket.h"

using ClientSpace::BuyAmmo;
using ClientSpace::BuyWeapon;
using ClientSpace::DefuseBomb;
using ClientSpace::Drop;
using ClientSpace::Equip;
using ClientSpace::MousePosition;
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

    std::string game_name = "mateo game";
    MapName map_name = MapName::DESIERTO;
    Skins skins(CounterTerroristSkin::GIGN, TerroristSkin::ARCTIC_AVENGER);

    CreateGame create_game(game_name, map_name, skins);

    // Act
    protocol.send_create_game(create_game);

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

    map_name_t map_code;
    accepted.recvall(&map_code, sizeof(map_code));
    EXPECT_EQ(static_cast<MapName>(map_code), map_name);

    skin_t ct_skin;
    skin_t t_skin;
    accepted.recvall(&ct_skin, sizeof(ct_skin));
    accepted.recvall(&t_skin, sizeof(t_skin));
    EXPECT_EQ(static_cast<CounterTerroristSkin>(ct_skin), skins.ct_skin);
    EXPECT_EQ(static_cast<TerroristSkin>(t_skin), skins.tt_skin);
}

TEST(ClientProtocolTest, SendJoinGameSendCorrectObject) {
    // Arrange
    Socket server_listener("9999");
    Socket client("localhost", "9999");
    Socket accepted = server_listener.accept();
    ClientProtocol protocol(client);

    std::string game_name = "join_test";
    Skins skins(CounterTerroristSkin::GSG9, TerroristSkin::GUERRILLA);
    JoinGame join_game(game_name, skins);

    // Act
    protocol.send_join_game(join_game);

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

    skin_t ct_skin;
    skin_t t_skin;
    accepted.recvall(&ct_skin, sizeof(ct_skin));
    accepted.recvall(&t_skin, sizeof(t_skin));
    EXPECT_EQ(static_cast<CounterTerroristSkin>(ct_skin), skins.ct_skin);
    EXPECT_EQ(static_cast<TerroristSkin>(t_skin), skins.tt_skin);
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
    MoveType move = MoveType::RIGHT;
    std::unique_ptr<InterfaceClientAction> action = std::make_unique<Move>(move);

    // Act
    action->action(protocol);

    // Arrange
    accepted.recvall(&command, sizeof(command));
    EXPECT_EQ(static_cast<PlayerCommandType>(command), PlayerCommandType::MOVE);
    accepted.recvall(&move_type, sizeof(move_type));
    EXPECT_EQ(static_cast<MoveType>(move_type), MoveType::RIGHT);
}

TEST(ClientProtocolTest, ReadGameInfoReadsCorrectData) {
    Socket server_socket("9999");

    GameInfo expected_game_info;
    expected_game_info.walls.push_back(Position(1, 2));
    expected_game_info.walls.push_back(Position(3, 4));

    std::thread server_thread([&]() {
        Socket client_socket = server_socket.accept();

        length_game_info_t size_to_send =
                htons(static_cast<length_game_info_t>(expected_game_info.walls.size()));
        client_socket.sendall(&size_to_send, sizeof(size_to_send));

        for (const Position& pos: expected_game_info.walls) {
            // Enviar coordenada x
            coordinate_t x_to_send = htons(pos.x);
            client_socket.sendall(&x_to_send, sizeof(coordinate_t));

            coordinate_t y_to_send = htons(pos.y);
            client_socket.sendall(&y_to_send, sizeof(coordinate_t));
        }
    });

    Socket client_socket("localhost", "9999");
    ClientProtocol protocol(client_socket);

    GameInfo received_game_info = protocol.read_game_info();

    ASSERT_EQ(received_game_info.walls.size(), expected_game_info.walls.size());

    for (size_t i = 0; i < expected_game_info.walls.size(); ++i) {
        ASSERT_EQ(received_game_info.walls[i].x, expected_game_info.walls[i].x);
        ASSERT_EQ(received_game_info.walls[i].y, expected_game_info.walls[i].y);
    }
    server_thread.join();
}