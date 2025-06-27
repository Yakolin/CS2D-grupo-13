#ifndef SENDER_H
#define SENDER_H

#include <memory>
#include <utility>

#include "../../common/game_image.h"
#include "../../common/player_command_types.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "protocol.h"

#define QUEUE_MAX_SIZE 10000

class Sender: public Thread {
protected:
    player_id_t& client_id;
    std::shared_ptr<Queue<GameImage>>& send_queue;
    ServerProtocol protocol;
    bool closed;

public:
    explicit Sender(player_id_t& client_id, Socket& socket,
                    std::shared_ptr<Queue<GameImage>>& send_queue);
    ~Sender();
    void run() override;
};


#endif  // H
