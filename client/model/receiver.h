#ifndef RECEIVER_H
#define RECEIVER_H

#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "protocol.h"

class Receiver: public Thread {
private:
    Queue<GameImage>& recv_queue;
    ClientProtocol protocol;

public:
    explicit Receiver(Socket& socket, Queue<GameImage>& recv_queue);
    ~Receiver() override;

    void run() override;
    void stop() override;
};

#endif  // !RECEIVER_H