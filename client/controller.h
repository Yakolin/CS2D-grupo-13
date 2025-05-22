#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "model/sender.h"
#include "model/client_action.h"
#include "../common/queue.h"
#include "../common/socket.h"
#include <SDL.h>
#include <iostream>
#include <memory>

#include "tipos.h"
class Controller {
private:
    Queue<std::unique_ptr<InterfaceClientAction>> send_queue;
    Sender sender;
public:
    explicit Controller(Socket& skt) ;

    /*
    pre:
    post: envia las cordenadas del mause en pixeles , puedes castear con las dimenciones del mapa
    */
    void sender_pos_mouse(int x, int y);
    /*
    pre:
    post:envia el mov del jugaodor
    */
    void sender_mov_player(SDL_Keycode tecla);


    void run();

    ~Controller();
};

#endif  // CONTROLLER_H
