#include "controller.h"
#include <SDL.h>


Controller::Controller() = default;

void Controller::sender_pos_mouse(int x, int y){
    int tile_size = 32; // tamaño en pixeles de cada bloque del mapa

    int col = x / tile_size; // columna en la matriz
    int fil = y / tile_size; // fila en la matriz
    ///... resto de codigo

}

void Controller::sender_mov_player(SDL_Keycode key) {
    enum class Movement { UP, DOWN, LEFT, RIGHT, NONE };
    Movement mov = Movement::NONE;

    switch (key) {
        case SDLK_w:
            mov = Movement::UP;
            break;
        case SDLK_s:
            mov = Movement::DOWN;
            break;
        case SDLK_a:
            mov = Movement::LEFT;
            break;
        case SDLK_d:
            mov = Movement::RIGHT;
            break;
        default:
            mov = Movement::NONE;
            break;
    }
}

void Controller::run() {}
