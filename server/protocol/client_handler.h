#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <memory>
#include <utility>

#include "../common/game_image.h"
#include "../common/player_types.h"
#include "../common/queue.h"
#include "../common/socket.h"
#include "protocol/protocol.h"
#include "protocol/receiver.h"
#include "protocol/sender.h"

#include "games_monitor.h"

#define QUEUE_MAX_SIZE 10000

class ClientHandler {
private:
    player_id_t player_id;
    Socket socket;
    std::shared_ptr<Queue<GameImage>> send_queue;
    Sender sender;
    Receiver receiver;

public:
    ClientHandler(player_id_t player_id, Socket&& socket, GamesMonitor& games_monitor);
    ~ClientHandler();
    void start();
    void stop();
    bool is_alive();
};

#endif  // !CLIENT_HANDLER_H