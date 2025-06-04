#include <memory>

#include <gtest/gtest.h>

#include "../../common/socket.h"
#include "../../server/acceptor.h"
#include "../../server/protocol/client_handler.h"
#include "../../server/protocol/games_monitor.h"
#include "../mocks/mock_games_monitor.h"
/*
TEST(ServerTest, ClientHandlerStopRunningCorrectly) {
    // Arrange
    Socket server_socket("9999");

    std::thread client_thread([] {
        Socket client_socket("localhost", "9999");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    });

    Socket accepted = server_socket.accept();

    GamesMonitor games_monitor;
    player_id_t player_id = 4;
    std::unique_ptr<ClientHandler> client =
            std::make_unique<ClientHandler>(player_id, std::move(accepted), games_monitor);


    // Act
    client->start();
    client->stop();
    client->join();

    // Assert
    EXPECT_FALSE(client->is_alive());

    client_thread.join();
}

TEST(ServerTest, GameWithOnePlayerCreatesCorrectly) {
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

    Socket accepted = server_socket.accept();
    GamesMonitor games_monitor;
    player_id_t player_id = 4;
    std::unique_ptr<ClientHandler> client =
            std::make_unique<ClientHandler>(player_id, std::move(accepted), games_monitor);

    // Act
    client->start();
    while (!games_monitor.has_active_games()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    games_monitor.clear();

    // Arrange
    EXPECT_FALSE(games_monitor.has_active_games());

    client->stop();
    client->join();
    client_thread.join();
}

TEST(ServerTest, GameWithOnePlayerAndAFewActionInQueueCreateAndDestroyCorrectly) {
    Socket server_socket("9999");

    std::thread client_thread([]() {
        Socket client_socket("localhost", "9999");
        std::string game_name = "mateo game";
        lobby_command_t command = static_cast<lobby_command_t>(LobbyCommandType::CREATE_GAME);
        client_socket.sendall(&command, sizeof(command));

        length_name_t length_name = htons(static_cast<length_name_t>(game_name.size()));
        client_socket.sendall(&length_name, sizeof(length_name_t));
        client_socket.sendall(game_name.c_str(), game_name.size());

        player_command_t player_command = static_cast<player_command_t>(PlayerCommandType::MOVE);
        client_socket.sendall(&player_command, sizeof(player_command_t));

        move_t move_type = static_cast<move_t>(MoveType::RIGHT);
        client_socket.sendall(&move_type, sizeof(move_t));
    });

    Socket accepted = server_socket.accept();
    GamesMonitor games_monitor;
    player_id_t player_id = 4;
    std::unique_ptr<ClientHandler> client =
            std::make_unique<ClientHandler>(player_id, std::move(accepted), games_monitor);

    // Act
    client->start();
    while (!games_monitor.has_active_games()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    games_monitor.clear();

    // Arrange
    EXPECT_FALSE(games_monitor.has_active_games());

    client->stop();
    client->join();
    client_thread.join();
}
*/