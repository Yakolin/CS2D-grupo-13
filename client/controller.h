#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>

#include "../common/game_image.h"
#include "../common/queue.h"
#include "../common/socket.h"
#include "model/client_action.h"
#include "model/receiver.h"
#include "model/sender.h"

#include "tipos.h"

class Controller {
private:
    Socket skt;
    std::shared_ptr<Queue<std::unique_ptr<InterfaceClientAction>>> send_queue;
    std::shared_ptr<Queue<GameImage>> recv_queue;
    Sender sender;
    Receiver receiver;

    void start();

public:
    explicit Controller(Socket&& skt);

    /*
    pre:
    post: envía las coordenadas del mouse en píxeles, puedes castearlas con las dimensiones del mapa
    */
    void sender_pos_mouse(int x, int y);


    void stop();
    /*
    pre:
    post: envía el movimiento del jugador
    */
    void sender_mov_player(SDL_Keycode tecla);

    bool has_game_image(GameImage& snapshot);

    void run();

    ~Controller();
};

#endif  // CONTROLLER_H
