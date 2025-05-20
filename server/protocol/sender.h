#ifndef SENDER_H
#define SENDER_H

#include <memory>

#include "../../common/game_image.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "protocol.h"

#define QUEUE_MAX_SIZE 10000


class Sender: public Thread {
protected:
    Queue<GameImage> send_queue;
    ServerProtocol protocol;
    bool closed;

public:
    explicit Sender(Socket& socket);
    ~Sender() = default;
    void run() override;
    void stop() override;
    void send(GameImage& game_image);
};


#endif  // H