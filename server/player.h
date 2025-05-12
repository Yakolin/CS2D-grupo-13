#ifndef PLAYER_H
#define PLAYER_H

#include "sender.h"
#include "receiver.h"
#include "common/socket.h"
#include <utility>

class Player
{
private:
    Socket socket;
    Sender sender;
    Receiver receiver;

public:
    Player(Socket &&socket);
    ~Player() = default;

    void run();
    void stop();
};

#endif // !PLAYER_H
