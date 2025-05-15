#include <memory>
#include <thread>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../common/socket.h"
#include "../server/protocol.h"
#include "mocks/mock_game.h"

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
    EXPECT_CALL(mock_game, buy_ammo(player_id, WeaponType::PRIMARY, 10)).Times(1);

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
        weapon_type_t weapon_type = static_cast<weapon_type_t>(WeaponType::PRIMARY);
        client_socket.sendall(reinterpret_cast<char*>(&weapon_type), sizeof(weapon_type));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<InterfacePlayerAction> action = protocol.read_reload(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::RELOAD);
    EXPECT_CALL(mock_game, reload(player_id, WeaponType::PRIMARY)).Times(1);

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
        weapon_type_t weapon_type = static_cast<weapon_type_t>(WeaponType::PRIMARY);
        ammo_t ammo_count = 10;
        client_socket.sendall(reinterpret_cast<char*>(&weapon_type), sizeof(weapon_type));
        client_socket.sendall(reinterpret_cast<char*>(&ammo_count), sizeof(ammo_count));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<InterfacePlayerAction> action = protocol.read_shoot(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::SHOOT);
    EXPECT_CALL(mock_game, shoot(player_id, WeaponType::PRIMARY, 10)).Times(1);

    // Ejecutamos la acción “inyectando” nuestro mock
    action->action(mock_game);

    client_thread.join();
}

TEST(ServerProtocolTest, ReadDropWeaponReturnCorrectObject) {
    // Arrange
    MockGame mock_game;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::DROP_WEAPON);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
        weapon_type_t weapon_type = static_cast<weapon_type_t>(WeaponType::PRIMARY);
        client_socket.sendall(reinterpret_cast<char*>(&weapon_type), sizeof(weapon_type));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<InterfacePlayerAction> action = protocol.read_drop_weapon(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::DROP_WEAPON);
    EXPECT_CALL(mock_game, drop_weapon(player_id)).Times(1);

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

TEST(ServerProtocolTest, ReadDropBombReturnCorrectObject) {
    // Arrange
    MockGame mock_game;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::DROP_BOMB);
        client_socket.sendall(reinterpret_cast<char*>(&command), sizeof(command));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<InterfacePlayerAction> action = protocol.read_drop_bomb(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::DROP_BOMB);
    EXPECT_CALL(mock_game, drop_bomb(player_id)).Times(1);

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