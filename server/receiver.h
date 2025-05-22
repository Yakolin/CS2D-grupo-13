#ifndef RECEIVER_H
#define RECEIVER_H

#include "common/socket.h"
#include "protocol.h"
#include "common/thread.h"
#include "common/queue.h"
#include "player_action.h"

class Receiver : public Thread
{
private:
    uint16_t &player_id;
    ServerProtocol protocol;
    Queue<std::shared_ptr<PlayerAction>> &recv_queue;
    bool closed;

public:
    Receiver(uint16_t &player_id, Socket &socket, Queue<std::shared_ptr<PlayerAction>> &recv_queue);
    ~Receiver();
    void run() override;
};
#endif // !RECEIVER_H