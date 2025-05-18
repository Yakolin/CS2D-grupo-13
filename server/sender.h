#ifndef SENDER_H
#define SENDER_H

#include "common/game_image.h"
#include "common/queue.h"
#include "common/socket.h"
#include "common/thread.h"

#include "protocol.h"

class Sender: public Thread {
private:
    ServerProtocol protocol;
    Queue<GameImage> send_queue;
    bool closed;

public:
    explicit Sender(Socket& socket);
    virtual ~Sender();
};

class LobbySender: public Sender {
private:
    Queue <
}

#endif  // H
