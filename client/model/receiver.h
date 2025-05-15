#ifndef RECEIVER_H
#define RECEIVER_H

#include "../../common/game_image.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "protocol.h"

class Receiver: public Thread {
private:
    bool closed;
    ClientProtocol protocol;
    Queue<GameImage>& recv_queue;

public:
    explicit Receiver(Socket& socket, Queue<GameImage>& recv_queue);
    ~Receiver() override;

    void run() override;
};

#endif  // !RECEIVER_H