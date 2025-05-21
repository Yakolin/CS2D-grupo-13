#ifndef RECEIVER_H
#define RECEIVER_H

#include <memory>
#include <vector>

#include "../../common/connection_closed_exception.h"
#include "../../common/game_image.h"
#include "../../common/player_command_types.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"

#include "client_action.h"
#include "functor_parse_client_action.h"
#include "games_monitor.h"
#include "protocol.h"


class Receiver: public Thread {
private:
    player_id_t& player_id;
    ServerProtocol protocol;
    std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>> recv_queue;
    std::shared_ptr<Queue<GameImage>>& send_queue;
    GamesMonitor& games_monitor;
    bool closed;

    void run_lobby();
    void run_game();

public:
    Receiver(player_id_t& player_id, Socket& socket, std::shared_ptr<Queue<GameImage>>& send_queue,
             GamesMonitor& games_monitor);
    ~Receiver();
    void run() override;
};

#endif  // !RECEIVER_H