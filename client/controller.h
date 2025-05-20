#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "tipos.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>       
#include <sstream>       
#include <stdexcept>  
#include <SDL.h>
class Controller {
private:

public:
        Controller() ;
    /*
    pre:
    post: envia las cordenadas del mause en pixeles , puedes castear con las dimenciones del mapa
    */
    void sender_pos_mouse(int x, int y);
    /*
    pre:
    post:envia el mov del jugaodor
    */
    void sender_mov_player( SDL_Keycode tecla);


    void run();
};

#endif // CONTROLLER_H