#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <memory>
#include <utility>

#include "../../common/lobby_types.h"
#include "../../common/player_types.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../protocol/receiver.h"
#include "../protocol/sender.h"

#include "games_monitor.h"

#define QUEUE_MAX_SIZE 10000

class ClientHandler {
private:
    player_id_t client_id;
    Socket socket;
    std::unique_ptr<Receiver> receiver;
    std::unique_ptr<Sender> sender;
    bool in_lobby;
    void stop_threads();

public:
    ClientHandler(player_id_t client_id, Socket&& socket, GamesMonitor& games_monitor);
    ~ClientHandler();

    void run_lobby(GamesMonitor& games_monitor);
    void send_handshake();
    void send_list_games(std::vector<std::string>& list_games);

    void run_game();

    void stop();
};

#endif  // !CLIENT_HANDLER_H
