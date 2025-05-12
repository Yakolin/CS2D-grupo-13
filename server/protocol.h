#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "common/socket.h"
#include "common/lobby_action.h"

class ServerProtocol
{
private:
    Socket &socket;

public:
    explicit ServerProtocol(Socket &socket);
    ~ServerProtocol();
    LobbyAction read_lobby_action();
};

#endif // !PROTOCOL_H