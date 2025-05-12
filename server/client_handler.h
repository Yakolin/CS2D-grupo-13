#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include "common/socket.h"
#include "games_monitor.h"
#include <utility>
#include "../common/lobby_action.h"

class ClientHandler : public Thread
{
private:
    uint16_t client_id;
    Socket socket;
    GamesMonitor &games_monitor;
    ServerProtocol protocol;
    bool in_lobby;

public:
    ClientHandler(uint16_t client_id, Socket &&socket, GamesMonitor &games_monitor);
    ~ClientHandler();
    void run() override;
    void stop() override;
};

#endif // !CLIENT_HANDLER_H
