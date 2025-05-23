#include <memory>
#include <string>
#include <thread>

#include <arpa/inet.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../common/game_image.h"
#include "../common/lobby_types.h"
#include "../common/player_command_types.h"
#include "../common/socket.h"
#include "../server/protocol/client_action.h"
#include "../server/protocol/protocol.h"
#include "mocks/mock_game.h"

using ServerSpace::BuyAmmo;
using ServerSpace::BuyWeapon;
using ServerSpace::CreateGame;
using ServerSpace::DefuseBomb;
using ServerSpace::Drop;
using ServerSpace::Equip;
using ServerSpace::Move;
using ServerSpace::PlantBomb;
using ServerSpace::Reload;
using ServerSpace::Shoot;

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
        lobby_command_t command = static_cast<lobby_command_t>(LobbyCommandType::CREATE_GAME);
        client_socket.sendall(&command, sizeof(command));

        length_name_t length_name = htons(static_cast<length_name_t>(game_name.size()));
        client_socket.sendall(&length_name, sizeof(length_name_t));
        client_socket.sendall(game_name.c_str(), game_name.size());
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    LobbyCommandType command = protocol.read_lobby_command();
    std::string game_name = protocol.read_create_game();

    // Assert
    ASSERT_EQ(command, LobbyCommandType::CREATE_GAME);
    ASSERT_EQ(game_name, "mateo game");


    client_thread.join();
}

TEST(ServerProtocolTest, ReadJoinGameReturnCorrectObject) {
    Socket server_socket("9999");
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");
        std::string game_name = "mateo game";
        lobby_command_t command = static_cast<lobby_command_t>(LobbyCommandType::JOIN_GAME);
        client_socket.sendall(&command, sizeof(command));

        length_name_t length_name = htons(static_cast<length_name_t>(game_name.size()));
        client_socket.sendall(&length_name, sizeof(length_name_t));
        client_socket.sendall(game_name.c_str(), game_name.size());
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    LobbyCommandType command = protocol.read_lobby_command();
    std::string game_name = protocol.read_join_game();

    // Assert
    ASSERT_EQ(command, LobbyCommandType::JOIN_GAME);
    ASSERT_EQ(game_name, "mateo game");

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

TEST(ServerProtocolTest, SendHandshakeReturnCorrectObject) {
    // Arrange
    Socket server_listener("9999");
    std::thread client_thread([&]() {
        Socket client("localhost", "9999");

        uint8_t recv_handshake;
        client.recvall(&recv_handshake, sizeof(recv_handshake));
        EXPECT_EQ(recv_handshake, static_cast<uint8_t>(HandshakeType::HANDSHAKE));

        uint16_t net_player_id;
        client.recvall(&net_player_id, sizeof(net_player_id));
        uint16_t player_id = ntohs(net_player_id);
        EXPECT_EQ(player_id, 123u);
    });

    Socket server_sock = server_listener.accept();
    ServerProtocol protocol(server_sock);
    player_id_t pid = 123;

    // Act
    protocol.send_player_id(pid);

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
        client_socket.sendall(&command, sizeof(player_command_t));
        weapon_code_t weapon_type = static_cast<weapon_code_t>(WeaponCode::AK47);
        client_socket.sendall(&weapon_type, sizeof(weapon_code_t));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<IActionToPlayer> action = protocol.read_buy_weapon(player_id);

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
        client_socket.sendall(&command, sizeof(player_command_t));
        weapon_type_t weapon_type = static_cast<weapon_type_t>(WeaponType::PRIMARY);
        ammo_t ammo_count = 10;
        ammo_count = htons(ammo_count);
        client_socket.sendall(&weapon_type, sizeof(weapon_type_t));
        client_socket.sendall(&ammo_count, sizeof(ammo_t));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<IActionToPlayer> action = protocol.read_buy_ammo(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::BUY_AMMO);
    EXPECT_CALL(mock_game, buy_ammo(player_id, WeaponType::PRIMARY, static_cast<ammo_t>(10)))
            .Times(1);

    // Ejecutamos la acción “inyectando” nuestro mock
    action->action(mock_game);

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
        client_socket.sendall(&x, sizeof(coordinate_t));
        client_socket.sendall(&y, sizeof(coordinate_t));
        client_socket.sendall(&ammo_count, sizeof(ammo_t));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act

    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<IActionToPlayer> action = protocol.read_shoot(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::SHOOT);
    EXPECT_CALL(mock_game, shoot(player_id, Position(1, 1), 10)).Times(1);

    // Ejecutamos la acción “inyectando” nuestro mock
    action->action(mock_game);

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

TEST(ServerProtocolTest, ReadDefuseBombReturnCorrectCommand) {
    // Arrange
    MockGame mock_game;
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

TEST(ServerProtocolTest, ReadEquipReturnCorrectObject) {
    // Arrange
    MockGame mock_game;
    Socket server_socket("9999");
    player_id_t player_id = 1;
    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");

        player_command_t command = static_cast<player_command_t>(PlayerCommandType::EQUIP);
        client_socket.sendall(&command, sizeof(player_command_t));
        equip_type_t equip_type = static_cast<equip_type_t>(EquipType::ROLL_DOWN);
        client_socket.sendall(&equip_type, sizeof(equip_type_t));
    });

    Socket server_client = server_socket.accept();
    ServerProtocol protocol(server_client);

    // Act
    PlayerCommandType command = protocol.read_player_command();
    std::unique_ptr<IActionToPlayer> action = protocol.read_equip(player_id);

    // Assert
    ASSERT_EQ(command, PlayerCommandType::EQUIP);
    EXPECT_CALL(mock_game, equip(player_id, EquipType::ROLL_DOWN)).Times(1);

    // Ejecutamos la acción “inyectando” nuestro mock
    action->action(mock_game);

    client_thread.join();
}
