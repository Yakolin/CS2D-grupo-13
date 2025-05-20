#ifndef PLAYER_HANDLER_H
#define PLAYER_HANDLER_H


#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../protocol/receiver.h"
#include "../protocol/sender.h"


class PlayerHandler {
private:
    player_id_t client_id;
    Socket socket;
    Receiver receiver;
    Sender sender;

public:
    PlayerHandler(player_id_t&& id, Socket&& socket,
                  std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>>& recv_game_queue);
    ~PlayerHandler();
    void start();
    void stop();
    void send(GameImage& game_image);
};


#endif  // !PLAYER_HANDLER_H