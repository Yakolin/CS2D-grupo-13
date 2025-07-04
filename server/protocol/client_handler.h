#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <memory>
#include <utility>

#include "../../common/game_image.h"
#include "../../common/liberror.h"
#include "../../common/player_command_types.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../interfaces/interface_games_monitor.h"

#include "protocol.h"
#include "receiver.h"
#include "sender.h"

#define QUEUE_MAX_SIZE 10000

class ClientHandler {
private:
    player_id_t player_id;
    Socket socket;
    std::shared_ptr<Queue<GameImage>> send_queue;
    Sender sender;
    Receiver receiver;

public:
    ClientHandler(player_id_t player_id, Socket&& socket, InterfaceGamesMonitor& games_monitor);
    ~ClientHandler();
    void start();
    void stop();
    void join();
    bool is_alive();
};

#endif  // !CLIENT_HANDLER_H
