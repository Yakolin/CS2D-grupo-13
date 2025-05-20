#ifndef RECEIVER_H
#define RECEIVER_H

#include <memory>

#include "../../common/player_types.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "client_action.h"
#include "functor_parse_client_action.h"
#include "protocol.h"


class Receiver: public Thread {
private:
    player_id_t& player_id;
    ServerProtocol protocol;
    std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>>& recv_queue;
    bool closed;

public:
    Receiver(player_id_t& player_id, Socket& socket,
             std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>>& recv_queue);
    ~Receiver();
    void run() override;
    void stop() override;
};

#endif  // !RECEIVER_H