#include <memory>
#include <string>
#include <thread>

#include <arpa/inet.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../common/socket.h"
#include "../server/client_action.h"
#include "../server/protocol.h"
#include "mocks/mock_game.h"

using Server::BuyAmmo;
using Server::BuyWeapon;
using Server::CreateGame;
using Server::DefuseBomb;
using Server::Drop;
using Server::Equip;
using Server::JoinGame;
using Server::ListGames;
using Server::Move;
using Server::PlantBomb;
using Server::Reload;
using Server::Shoot;

TEST(ServerProtocolTest, ReadPlayerCommandReturnCorrectType) {
    // Arrange
    Socket server_socket("9999");

    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::MOVE);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
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
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act
    LobbyCommandType result = protocol.read_lobby_command();

    // Assert
    EXPECT_EQ(result, LobbyCommandType::CREATE_GAME);

    client_thread.join();
}
/*

TEST(ServerProtocolTest, ReadCreateGameReturnCorrectObject) {
    // Arrange
    MockGame mock_game;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::string game_name = "mateo game";
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        lobby_command_t command = static_cast<lobby_command_t>(LobbyCommandType::CREATE_GAME);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));

        client_socket.sendall(reinterpret_cast<char*>(&weapon_type), sizeof(weapon_type));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<InterfacePlayerAction> action = protocol.read_buy_weapon(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::BUY_WEAPON);
    EXPECT_CALL(mock_game, buy_weapon(player_id, WeaponCode::AK47)).Times(1);

    // Ejecutamos la acción “inyectando” nuestro mock
    action->action(mock_game);

    client_thread.join();
}
*/

TEST(ServerProtocolTest, ReadBuyWeapontReturnCorrectObject) {
    // Arrange
    MockGame mock_game;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::BUY_WEAPON);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
        weapon_code_t weapon_type = static_cast<weapon_code_t>(WeaponCode::AK47);
        client_socket.sendall(reinterpret_cast<char*>(&weapon_type), sizeof(weapon_type));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<InterfacePlayerAction> action = protocol.read_buy_weapon(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::BUY_WEAPON);
    EXPECT_CALL(mock_game, buy_weapon(player_id, WeaponCode::AK47)).Times(1);

    // Ejecutamos la acción “inyectando” nuestro mock
    action->action(mock_game);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadBuyAmmoReturnCorrectObject) {
    // Arrange
    MockGame mock_game;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::BUY_AMMO);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
        weapon_type_t weapon_type = static_cast<weapon_type_t>(WeaponType::PRIMARY);
        ammo_t ammo_count = 10;
        ammo_count = htons(ammo_count);
        client_socket.sendall(reinterpret_cast<char*>(&weapon_type), sizeof(weapon_type));
        client_socket.sendall(reinterpret_cast<char*>(&ammo_count), sizeof(ammo_count));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<InterfacePlayerAction> action = protocol.read_buy_ammo(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::BUY_AMMO);
    EXPECT_CALL(mock_game, buy_ammo(player_id, WeaponType::PRIMARY, static_cast<ammo_t>(10)))
            .Times(1);

    // Ejecutamos la acción “inyectando” nuestro mock
    action->action(mock_game);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadReloadReturnCorrectObject) {
    // Arrange
    MockGame mock_game;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::RELOAD);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<InterfacePlayerAction> action = protocol.read_reload(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::RELOAD);
    EXPECT_CALL(mock_game, reload(player_id)).Times(1);

    // Ejecutamos la acción “inyectando” nuestro mock
    action->action(mock_game);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadShootReturnCorrectObject) {
    // Arrange
    MockGame mock_game;
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
        client_socket.sendall(reinterpret_cast<char*>(&x), sizeof(x));
        client_socket.sendall(reinterpret_cast<char*>(&y), sizeof(y));
        client_socket.sendall(reinterpret_cast<char*>(&ammo_count), sizeof(ammo_count));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<InterfacePlayerAction> action = protocol.read_shoot(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::SHOOT);
    EXPECT_CALL(mock_game, shoot(player_id, Position(1, 1), 10)).Times(1);

    // Ejecutamos la acción “inyectando” nuestro mock
    action->action(mock_game);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadPlantBombReturnCorrectObject) {
    // Arrange
    MockGame mock_game;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::PLANT_BOMB);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<InterfacePlayerAction> action = protocol.read_plant_bomb(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::PLANT_BOMB);
    EXPECT_CALL(mock_game, plant_bomb(player_id)).Times(1);

    // Ejecutamos la acción “inyectando” nuestro mock
    action->action(mock_game);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadDefuseBombReturnCorrectObject) {
    // Arrange
    MockGame mock_game;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::DEFUSE_BOMB);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<InterfacePlayerAction> action = protocol.read_defuse_bomb(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::DEFUSE_BOMB);
    EXPECT_CALL(mock_game, defuse_bomb(player_id)).Times(1);

    // Ejecutamos la acción “inyectando” nuestro mock
    action->action(mock_game);

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

TEST(ServerProtocolTest, ReadDropReturnCorrectObject) {
    // Arrange
    MockGame mock_game;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::DROP);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<InterfacePlayerAction> action = protocol.read_drop(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::DROP);
    EXPECT_CALL(mock_game, drop(player_id)).Times(1);

    // Ejecutamos la acción “inyectando” nuestro mock
    action->action(mock_game);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadEquipReturnCorrectObject) {
    // Arrange
    MockGame mock_game;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::EQUIP);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
        equip_type_t equip_type = static_cast<equip_type_t>(EquipType::ROLL_DOWN);
        client_socket.sendall(reinterpret_cast<char*>(&equip_type), sizeof(equip_type));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act
    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<InterfacePlayerAction> action = protocol.read_equip(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::EQUIP);
    EXPECT_CALL(mock_game, equip(player_id, EquipType::ROLL_DOWN)).Times(1);

    // Ejecutamos la acción “inyectando” nuestro mock
    action->action(mock_game);

    client_thread.join();
}
