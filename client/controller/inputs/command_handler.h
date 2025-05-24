#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <memory>
#include <utility>

#include "../../common/game.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../model/client_action.h"
#include "../model/protocol.h"

class CommandHandler {  // deberia recibir la parte del front que envia teclas y procesarlas en
                        // handle_input, no se como se llama
private:
    std::shared_ptr<Queue<GameImage>>& send_queue;
    ClientProtocol protocol;
    void handle_input(std::unique_ptr<InterfaceClientAction>& action);

public:
    CommandHandler(shared_ptr<Queue<GameImage>>& send_queue, Socket& skt);
    ~CommandHandler();
    void run();  // deberia recibir por parametro la parte del front que envia teclas y procesarlas
                 // en handle_input, no se como se llama
};

#endif  // !COMMAND_HANDLER_H