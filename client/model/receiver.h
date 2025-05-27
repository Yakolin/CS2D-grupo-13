#ifndef RECEIVER_H
#define RECEIVER_H

#include <memory>
#include <utility>

#include "../../common/game_image.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "protocol.h"

class Receiver: public Thread {
private:
    bool closed;
    ClientProtocol protocol;
    std::shared_ptr<Queue<GameImage>>& recv_queue;

public:
    explicit Receiver(Socket& socket, std::shared_ptr<Queue<GameImage>>& recv_queue);
    ~Receiver() override;

    void run() override;
};

#endif  // !RECEIVER_H