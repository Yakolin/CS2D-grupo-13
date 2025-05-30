#ifndef RECEIVER_H
#define RECEIVER_H

#include <memory>
#include <vector>

#include "../../common/connection_closed_exception.h"
#include "../../common/game_image.h"
#include "../../common/liberror.h"
#include "../../common/player_command_types.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../interfaces/interface_games_monitor.h"

#include "client_action.h"
#include "functor_parse_client_action.h"
#include "protocol.h"


class Receiver: public Thread {
private:
    player_id_t& player_id;
    ServerProtocol protocol;
    std::shared_ptr<Queue<std::unique_ptr<ClientAction>>> recv_queue;
    std::shared_ptr<Queue<GameImage>>& send_queue;
    InterfaceGamesMonitor& games_monitor;
    bool closed;

    void run_lobby();
    void run_game();

public:
    Receiver(player_id_t& player_id, Socket& socket, std::shared_ptr<Queue<GameImage>>& send_queue,
             InterfaceGamesMonitor& games_monitor);
    ~Receiver();
    void run() override;
    void stop() override;
};

#endif  // !RECEIVER_H