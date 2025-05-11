#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "common/socket.h"

class ServerProtocol
{
private:
    Socket &socket;

public:
    explicit ServerProtocol(Socket &socket);
    ~ServerProtocol();
};

#endif // !PROTOCOL_H