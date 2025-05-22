#ifndef SENDER_H
#define SENDER_H

#include "common/socket.h"
#include "common/thread.h"
#include "protocol.h"
#include "common/queue.h"
#include "common/game_image.h"

class Sender : public Thread
{
private:
    ServerProtocol protocol;
    Queue<GameImage> send_queue;
    bool closed;

public:
    explicit Sender(Socket &socket);
    ~Sender();
    void send(GameImage &game_image);
    void run() override;
    void stop() override;
};

#endif // H
