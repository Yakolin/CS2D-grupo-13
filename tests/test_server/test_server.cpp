#include <memory>

#include <gtest/gtest.h>

#include "../../common/socket.h"
#include "../../server/protocol/client_handler.h"
#include "../mocks/mock_games_monitor.h"

TEST(ServerTest, ClientHandlerStopRunningCorrectly) {
    // Arrange
    Socket server_socket("9999");

    std::thread client_thread([] {
        Socket client_socket("localhost", "9999");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    });

    Socket accepted = server_socket.accept();

    MockGamesMonitor games_monitor_mock;
    player_id_t player_id = 4;
    std::unique_ptr<ClientHandler> client =
            std::make_unique<ClientHandler>(player_id, std::move(accepted), games_monitor_mock);


    // Act
    client->start();
    client->stop();

    // Assert
    EXPECT_FALSE(client->is_alive());

    client_thread.join();
}
