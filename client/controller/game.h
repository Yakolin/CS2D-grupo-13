#ifndef GAME_H
#define GAME_H

#include <memory>
#include <utility>

#include "../../common/constant_rate_loop.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../game_image.h"
#include "../model/client_action.h"
#include "../model/receiver.h"
#include "../model/sender.h"
#include "inputs/command_handler.h"

#define MAX_QUEUE_SIZE 10000

class Game {
private:
    Socket& socket;
    std::shared_ptr<Queue<std::unique_ptr<InterfaceClientAction>>> send_queue;
    std::shared_ptr<Queue<GameImage>> recv_queue;
    Receiver receiver;
    Sender sender;
    CommandHandler command_handler;
    ConstantRateLoop constant_rate_loop;

    void step();
    void update_image();

public:
    Game(Socket& skt);
    ~Game();
    void run_game();
};

#endif  // !GAME_H