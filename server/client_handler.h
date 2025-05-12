#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include "common/socket.h"
#include "games_monitor.h"
#include <utility>

class ClientHandler : public Thread
{
private:
    Socket socket;
    GamesMonitor &games_monitor;
    ServerProtocol protocol;

public:
    ClientHandler(Socket &&socket, GamesMonitor &games_monitor);
    ~ClientHandler() = default;
    void run() override;
    void stop() override;
};

#endif // !CLIENT_HANDLER_H
