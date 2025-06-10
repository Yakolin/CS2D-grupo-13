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

    // --- Arrange: datos esperados que enviaremos desde el servidor ---
    GameInfo expected_game_info;

    expected_game_info.map_info.bomb_A = RectangleInfo(Position(10, 20), Position(30, 40));
    expected_game_info.map_info.bomb_B = RectangleInfo(Position(50, 60), Position(70, 80));
    expected_game_info.map_info.spawn_TT = RectangleInfo(Position(90, 100), Position(110, 120));
    expected_game_info.map_info.spawn_CT = RectangleInfo(Position(130, 140), Position(150, 160));

    expected_game_info.map_info.walls.push_back(Position(1, 2));
    expected_game_info.map_info.walls.push_back(Position(3, 4));

    expected_game_info.weapons_purchasables.emplace_back(WeaponCode::AK47, 2700);
    expected_game_info.weapons_purchasables.emplace_back(WeaponCode::M3, 3100);

    // --- Simulamos el servidor que envía los datos ---
    std::thread server_thread([&]() {
        Socket client_socket = server_socket.accept();

        auto send_position = [&](coordinate_t x, coordinate_t y) {
            coordinate_t x_net = htons(x);
            coordinate_t y_net = htons(y);
            client_socket.sendall(&x_net, sizeof(x_net));
            client_socket.sendall(&y_net, sizeof(y_net));
        };

        // 1. Enviar posiciones de zonas: bomb_A, bomb_B, spawn_TT, spawn_CT
        send_position(10, 20);
        send_position(30, 40);

        send_position(50, 60);
        send_position(70, 80);

        send_position(90, 100);
        send_position(110, 120);

        send_position(130, 140);
        send_position(150, 160);

        // 2. Enviar cantidad de paredes
        uint16_t wall_count = htons(expected_game_info.map_info.walls.size());
        client_socket.sendall(&wall_count, sizeof(wall_count));

        // 3. Enviar paredes
        for (const Position& wall: expected_game_info.map_info.walls) {
            send_position(wall.x, wall.y);
        }

        // 4. Enviar cantidad de armas (1 byte)
        uint8_t weapon_count = expected_game_info.weapons_purchasables.size();
        client_socket.sendall(&weapon_count, sizeof(weapon_count));

        // 5. Enviar armas: código (1 byte), precio (2 bytes)
        for (const WeaponInfo& weapon: expected_game_info.weapons_purchasables) {
            uint8_t code = static_cast<uint8_t>(weapon.code);
            uint16_t price = htons(weapon.price);
            client_socket.sendall(&code, sizeof(code));
            client_socket.sendall(&price, sizeof(price));
        }
    });

    // --- Cliente lee la info ---
    Socket client_socket("localhost", "9999");
    ClientProtocol protocol(client_socket);

    GameInfo received_game_info = protocol.read_game_info();

    // --- Asserts: comparar estructuras completas ---
    const auto& expected_map = expected_game_info.map_info;
    const auto& received_map = received_game_info.map_info;

    auto assert_position = [](const Position& a, const Position& b) {
        ASSERT_EQ(a.x, b.x);
        ASSERT_EQ(a.y, b.y);
    };

    assert_position(expected_map.bomb_A.pos_min, received_map.bomb_A.pos_min);
    assert_position(expected_map.bomb_A.pos_max, received_map.bomb_A.pos_max);
    assert_position(expected_map.bomb_B.pos_min, received_map.bomb_B.pos_min);
    assert_position(expected_map.bomb_B.pos_max, received_map.bomb_B.pos_max);
    assert_position(expected_map.spawn_TT.pos_min, received_map.spawn_TT.pos_min);
    assert_position(expected_map.spawn_TT.pos_max, received_map.spawn_TT.pos_max);
    assert_position(expected_map.spawn_CT.pos_min, received_map.spawn_CT.pos_min);
    assert_position(expected_map.spawn_CT.pos_max, received_map.spawn_CT.pos_max);

    ASSERT_EQ(received_map.walls.size(), expected_map.walls.size());
    for (size_t i = 0; i < expected_map.walls.size(); ++i) {
        assert_position(received_map.walls[i], expected_map.walls[i]);
    }

    const auto& expected_weapons = expected_game_info.weapons_purchasables;
    const auto& received_weapons = received_game_info.weapons_purchasables;

    ASSERT_EQ(received_weapons.size(), expected_weapons.size());
    for (size_t i = 0; i < expected_weapons.size(); ++i) {
        ASSERT_EQ(received_weapons[i].code, expected_weapons[i].code);
        ASSERT_EQ(received_weapons[i].price, expected_weapons[i].price);
    }

    server_thread.join();
}
