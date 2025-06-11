#include <memory>
#include <string>
#include <thread>

#include <arpa/inet.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../common/game_image.h"
#include "../../common/game_info.h"
#include "../../common/liberror.h"
#include "../../common/lobby_types.h"
#include "../../common/player_command_types.h"
#include "../../common/socket.h"
#include "../../server/protocol/client_action.h"
#include "../../server/protocol/protocol.h"
#include "../../server/protocol/receiver.h"
#include "../mocks/mock_games_monitor.h"
#include "../mocks/mock_player.h"

using ServerSpace::BuyWeapon;
using ServerSpace::Equip;
using ServerSpace::Move;
using ServerSpace::Reload;
using ServerSpace::Shoot;
/*
using ServerSpace::BuyAmmo;
*/

TEST(ServerProtocolTest, ReadPlayerCommandReturnCorrectType) {
    // Arrange
    Socket server_socket("9999");

    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::MOVE);
        client_socket.sendall(&command, sizeof(player_command_t));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act
    PlayerCommandType result = protocol.read_player_command();

    // Assert
    EXPECT_EQ(result, PlayerCommandType::MOVE);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadLobbyCommandReturnCorrectType) {
    // Arrange
    Socket server_socket("9999");

    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        lobby_command_t command = static_cast<lobby_command_t>(LobbyCommandType::CREATE_GAME);
        client_socket.sendall(&command, sizeof(lobby_command_t));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act
    LobbyCommandType result = protocol.read_lobby_command();

    // Assert
    EXPECT_EQ(result, LobbyCommandType::CREATE_GAME);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadCreateGameReturnCorrectObject) {
    // Arrange
    Socket server_socket("9999");
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");
        std::string game_name = "mateo game";
        MapName map_name = MapName::DESIERTO;
        Skins skins(CounterTerroristSkin::GIGN, TerroristSkin::ARCTIC_AVENGER);

        lobby_command_t command = static_cast<lobby_command_t>(LobbyCommandType::CREATE_GAME);
        client_socket.sendall(&command, sizeof(command));

        length_string_t length_name = htons(static_cast<length_string_t>(game_name.size()));
        client_socket.sendall(&length_name, sizeof(length_string_t));
        client_socket.sendall(game_name.c_str(), game_name.size());

        map_name_t map_code = static_cast<map_name_t>(map_name);
        client_socket.sendall(&map_code, sizeof(map_name_t));

        skin_t ct_skin = static_cast<skin_t>(skins.ct_skin);
        skin_t t_skin = static_cast<skin_t>(skins.tt_skin);
        client_socket.sendall(&ct_skin, sizeof(skin_t));
        client_socket.sendall(&t_skin, sizeof(skin_t));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act
    LobbyCommandType command = protocol.read_lobby_command();
    CreateGame create_game = protocol.read_create_game();

    // Assert
    ASSERT_EQ(command, LobbyCommandType::CREATE_GAME);
    ASSERT_EQ(create_game.game_name, "mateo game");
    ASSERT_EQ(create_game.map_name, MapName::DESIERTO);
    ASSERT_EQ(create_game.skins.ct_skin, CounterTerroristSkin::GIGN);
    ASSERT_EQ(create_game.skins.tt_skin, TerroristSkin::ARCTIC_AVENGER);

    client_thread.join();
}

TEST(ServerProtocolTest, SendGameInfoSendsCorrectData) {
    Socket server_socket("9999");

    // Arrange
    GameInfo game_info;

    game_info.map_info.bomb_A = RectangleInfo(Position(10, 20), Position(30, 40));
    game_info.map_info.bomb_B = RectangleInfo(Position(50, 60), Position(70, 80));
    game_info.map_info.spawn_TT = RectangleInfo(Position(90, 100), Position(110, 120));
    game_info.map_info.spawn_CT = RectangleInfo(Position(130, 140), Position(150, 160));

    game_info.map_info.walls.push_back(Position(1, 2));
    game_info.map_info.walls.push_back(Position(3, 4));

    game_info.weapons_purchasables.push_back(WeaponInfo{WeaponCode::AK47, 2700});
    game_info.weapons_purchasables.push_back(WeaponInfo{WeaponCode::M3, 3100});

    std::thread client_thread([&]() {
        Socket client_socket("localhost", "9999");

        auto recv_position = [&](coordinate_t expected_x, coordinate_t expected_y) {
            coordinate_t received_x, received_y;
            client_socket.recvall(&received_x, sizeof(received_x));
            client_socket.recvall(&received_y, sizeof(received_y));
            ASSERT_EQ(ntohs(received_x), expected_x);
            ASSERT_EQ(ntohs(received_y), expected_y);
        };

        recv_position(10, 20);
        recv_position(30, 40);

        recv_position(50, 60);
        recv_position(70, 80);

        recv_position(90, 100);
        recv_position(110, 120);

        recv_position(130, 140);
        recv_position(150, 160);

        uint16_t walls_count;
        client_socket.recvall(&walls_count, sizeof(walls_count));
        walls_count = ntohs(walls_count);
        ASSERT_EQ(walls_count, game_info.map_info.walls.size());

        for (const Position& wall: game_info.map_info.walls) {
            recv_position(wall.x, wall.y);
        }

        uint8_t weapon_count;
        client_socket.recvall(&weapon_count, sizeof(weapon_count));
        ASSERT_EQ(weapon_count, game_info.weapons_purchasables.size());

        for (const WeaponInfo& weapon: game_info.weapons_purchasables) {
            uint8_t received_code;
            client_socket.recvall(&received_code, sizeof(received_code));
            ASSERT_EQ(received_code, static_cast<uint8_t>(weapon.code));

            uint16_t received_price;
            client_socket.recvall(&received_price, sizeof(received_price));
            ASSERT_EQ(ntohs(received_price), weapon.price);
        }
    });

    //  Act
    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);
    protocol.send_game_info(game_info);

    client_thread.join();
}

TEST(ServerProtocolTest, ReceiveAckReadsCorrectData) {
    Socket server_socket("9999");

    // Arrange
    Acknowledge expected_ack = Acknowledge::READY;

    std::thread client_thread([&]() {
        Socket client_socket("localhost", "9999");
        acknowledge_t ack_type = static_cast<acknowledge_t>(expected_ack);
        client_socket.sendall(&ack_type, sizeof(ack_type));
    });

    // Act
    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);
    Acknowledge received_ack = protocol.read_acknowledge();

    // Assert
    ASSERT_EQ(received_ack, expected_ack);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadListGamesReturnCorrectCommand) {
    Socket server_socket("9999");
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");
        lobby_command_t command = static_cast<lobby_command_t>(LobbyCommandType::LIST_GAMES);
        client_socket.sendall(&command, sizeof(command));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act
    LobbyCommandType command = protocol.read_lobby_command();

    // Assert
    ASSERT_EQ(command, LobbyCommandType::LIST_GAMES);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadBuyWeapontReturnCorrectObject) {
    // Arrange
    MockPlayer mock_player;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::BUY_WEAPON);
        client_socket.sendall(&command, sizeof(player_command_t));
        weapon_code_t weapon_type = static_cast<weapon_code_t>(WeaponCode::AK47);
        client_socket.sendall(&weapon_type, sizeof(weapon_code_t));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<ClientAction> action = protocol.read_buy_weapon(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::BUY_WEAPON);
    EXPECT_CALL(mock_player, buy_weapon(WeaponCode::AK47)).Times(1);

    // Ejecutamos la acción inyectando nuestro mock de jugador
    action->action_to(mock_player);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadReloadReturnCorrectCommand) {
    // Arrange
    Socket server_socket("9999");
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::RELOAD);
        client_socket.sendall(&command, sizeof(player_command_t));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();

    // Assert
    ASSERT_EQ(command, PlayerCommandType::RELOAD);

    client_thread.join();
}

/*
TEST(ServerProtocolTest, ReadBuyAmmoReturnCorrectObject) {
    // Arrange
    MockPlayer mock_player;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command =
        static_cast<player_command_t>(PlayerCommandType::BUY_AMMO); client_socket.sendall(&command,
            sizeof(player_command_t)); weapon_type_t weapon_type =
            static_cast<weapon_type_t>(WeaponType::PRIMARY); ammo_t ammo_count = 10; ammo_count =
            htons(ammo_count); client_socket.sendall(&weapon_type, sizeof(weapon_type_t));
            client_socket.sendall(&ammo_count, sizeof(ammo_t));
            });

            Socket server_client = server_socket.accept();
ServerProtocol protocol(server_client);

// Act

PlayerCommandType command = protocol.read_player_command();
std::unique_ptr<ClientAction> action = protocol.read_buy_ammo(player_id);

// Assert
ASSERT_EQ(command, PlayerCommandType::BUY_AMMO);
EXPECT_CALL(mock_player, buy_ammo(WeaponType::PRIMARY, static_cast<ammo_t>(10))).Times(1);

// Ejecutamos la acción inyectando nuestro mock de jugador
action->action_to(mock_player);

client_thread.join();
}



TEST(ServerProtocolTest, ReadPlantBombReturnCorrectCommand) {
// Arrange
Socket server_socket("9999");
std::thread client_thread([]() {
Socket client_socket("localhost", "9999");

player_command_t command = static_cast<player_command_t>(PlayerCommandType::PLANT_BOMB);
client_socket.sendall(&command, sizeof(player_command_t));
});

Socket server_client = server_socket.accept();
ServerProtocol protocol(server_client);

// Act

PlayerCommandType command = protocol.read_player_command();

// Assert
ASSERT_EQ(command, PlayerCommandType::PLANT_BOMB);


client_thread.join();
}

*/
TEST(ServerProtocolTest, ReadShootReturnCorrectObject) {
    // Arrange
    MockPlayer mock_player;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::SHOOT);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
        coordinate_t x = 1;
        coordinate_t y = 1;
        ammo_t ammo_count = 10;
        x = htons(x);
        y = htons(y);
        ammo_count = htons(ammo_count);
        client_socket.sendall(&x, sizeof(coordinate_t));
        client_socket.sendall(&y, sizeof(coordinate_t));
        client_socket.sendall(&ammo_count, sizeof(ammo_t));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<ClientAction> action = protocol.read_shoot(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::SHOOT);
    EXPECT_CALL(mock_player, shoot(1, 1)).Times(1);

    // Ejecutamos la acción inyectando nuestro mock de jugador
    action->action_to(mock_player);

    client_thread.join();
}


TEST(ServerProtocolTest, ReadDefuseBombReturnCorrectCommand) {
    // Arrange
    Socket server_socket("9999");
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::DEFUSE_BOMB);
        client_socket.sendall(&command, sizeof(player_command_t));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();

    // Assert
    ASSERT_EQ(command, PlayerCommandType::DEFUSE_BOMB);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadPlayerCommandReturnConnectionClosedException) {
    // Arrange
    Socket server_socket("9999");
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");
        client_socket.close();
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act & Assert
    EXPECT_THROW(protocol.read_player_command(), ConnectionClosedException);

    client_thread.join();
}


TEST(ServerProtocolTest, ReadDropReturnCorrectCommand) {
    // Arrange
    Socket server_socket("9999");
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::DROP);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();

    // Assert
    ASSERT_EQ(command, PlayerCommandType::DROP);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadKnifeReturnCorrectObject) {
    // Arrange
    MockPlayer mock_player;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::EQUIP);
        client_socket.sendall(&command, sizeof(player_command_t));
        equip_type_t equip_type = static_cast<equip_type_t>(EquipType::KNIFE);
        client_socket.sendall(&equip_type, sizeof(equip_type_t));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act
    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<ClientAction> action = protocol.read_equip(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::EQUIP);
    EXPECT_CALL(mock_player, change_weapon(EquipType::KNIFE)).Times(1);

    // Ejecutamos la acción inyectando nuestro mock de jugador
    action->action_to(mock_player);

    client_thread.join();
}

/*

TEST(ServerProtocolIntegralTest, ReadCreateGameExecuteGamesMonitorCorrectly) {

Socket server_socket("9999");
MockGamesMonitor mock_games_monitor;
player_id_t expected_player_id = 1;
std::atomic<bool> command_processed = false;

EXPECT_CALL(mock_games_monitor,
create_game(expected_player_id, "mateo game", testing::_, testing::_, testing::_))
.Times(1)
.WillOnce(testing::Invoke([&command_processed](auto, auto, auto, auto, auto) {
command_processed = true;
return true;
}));

std::thread client_thread([]() {
 Socket client_socket("localhost", "9999");
 std::string game_name = "mateo game";
 lobby_command_t command = static_cast<lobby_command_t>(LobbyCommandType::CREATE_GAME);
 client_socket.sendall(&command, sizeof(command));

 length_string_t length_name = htons(static_cast<length_string_t>(game_name.size()));
 client_socket.sendall(&length_name, sizeof(length_string_t));
 client_socket.sendall(game_name.c_str(), game_name.size());
});

Socket server_client = server_socket.accept();

auto dummy_queue = std::make_shared<Queue<GameImage>>();
Receiver receiver(expected_player_id, server_client, dummy_queue, mock_games_monitor);

receiver.start();

while (!command_processed) {
 std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
receiver.stop();
receiver.join();
client_thread.join();
}

TEST(ServerProtocolIntegralTest, ReadJoinGameExecuteGamesMonitorCorrectly) {

Socket server_socket("9999");
MockGamesMonitor mock_games_monitor;
player_id_t expected_player_id = 1;
std::atomic<bool> command_processed = false;

EXPECT_CALL(mock_games_monitor,
join_game(expected_player_id, "mateo game", testing::_, testing::_, testing::_))
.Times(1)
.WillOnce(testing::Invoke([&command_processed](auto, auto, auto, auto, auto) {
command_processed = true;
return true;
}));

std::thread client_thread([]() {
Socket client_socket("localhost", "9999");
std::string game_name = "mateo game";
lobby_command_t command = static_cast<lobby_command_t>(LobbyCommandType::JOIN_GAME);
client_socket.sendall(&command, sizeof(command));

length_string_t length_name = htons(static_cast<length_string_t>(game_name.size()));
client_socket.sendall(&length_name, sizeof(length_string_t));
client_socket.sendall(game_name.c_str(), game_name.size());
});

Socket server_client = server_socket.accept();

auto dummy_queue = std::make_shared<Queue<GameImage>>();
Receiver receiver(expected_player_id, server_client, dummy_queue, mock_games_monitor);

receiver.start();

while (!command_processed) {
 std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
receiver.stop();
receiver.join();
client_thread.join();
}

TEST(ServerProtocolIntegralTest, ReadListGamesExecuteGamesMonitorCorrectly) {
Socket server_socket("9999");
MockGamesMonitor mock_games_monitor;
player_id_t expected_player_id = 1;
std::atomic<bool> command_processed = false;

// Esperamos que se llame a list_games, que es lo que hace LIST_GAMES
EXPECT_CALL(mock_games_monitor, list_games())
.Times(1)
.WillOnce(testing::Invoke([&command_processed]() {
 command_processed = true;
 return std::vector<std::string>{"game1", "game2"};
}));

// Cliente que envía el comando LIST_GAMES
std::thread client_thread([]() {
 Socket client_socket("localhost", "9999");
 lobby_command_t command = static_cast<lobby_command_t>(LobbyCommandType::LIST_GAMES);
 client_socket.sendall(&command, sizeof(command));
 // Espera un poco para permitir que el servidor procese
 std::this_thread::sleep_for(std::chrono::milliseconds(100));
});

Socket server_client = server_socket.accept();
auto dummy_queue = std::make_shared<Queue<GameImage>>();
Receiver receiver(expected_player_id, server_client, dummy_queue, mock_games_monitor);

receiver.start();

// Esperamos a que se procese el comando
while (!command_processed) {
 std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

// Cortamos manualmente el receiver
receiver.stop();
receiver.join();
client_thread.join();
}

*/