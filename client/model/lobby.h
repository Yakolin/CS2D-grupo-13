#ifndef LOBBY_H
#define LOBBY_H

#include "../../common/socket.h"

#include "protocol.h"
#include "receiver.h"
#include "sender.h"

class Lobby {
private:
    ClientProtocol protocol;

public:
    Lobby(Socket& socket);
};

#endif  // !LOBBY_H