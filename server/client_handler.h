#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <memory>
#include <utility>

#include "common/lobby_types.h"
#include "common/player_types.h"
#include "common/queue.h"
#include "common/socket.h"

#include "games_monitor.h"
#include "receiver.h"
#include "sender.h"

class ClientHandler {
private:
    player_id_t client_id;
    Socket socket;
    GamesMonitor& games_monitor;
    std::unique_ptr<Receiver> receiver;
    Sender sender;
    bool in_lobby;

public:
    ClientHandler(player_id_t client_id, Socket&& socket, GamesMonitor& games_monitor);
    ~ClientHandler();
    void run_lobby();
    void run_game();
    void stop();
};

#endif  // !CLIENT_HANDLER_H
