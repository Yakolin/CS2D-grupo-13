#ifndef PLAYER_H
#define PLAYER_H

#include "sender.h"
#include "receiver.h"
#include "common/socket.h"
#include <utility>

class Player
{
private:
    uint16_t player_id;
    Socket socket;
    Sender sender;
    Receiver receiver;

public:
    Player(uint16_t &&player_id, Socket &&socket);
    ~Player() = default;

    void run();
    void stop();
};

#endif // !PLAYER_H
