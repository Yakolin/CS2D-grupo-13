#include "controller.h"
#include <SDL.h>
#include <iostream>

Controller::Controller() = default;

void Controller::sender_pos_mouse(int x, int y){
    int tile_size = 32; // tamaño en pixeles de cada bloque del mapa

    int col = x / tile_size; // columna en la matriz
    int fil = y / tile_size; // fila en la matriz
    ///... resto de codigo
    std::cout << "Fila: " << fil << ", Columna: " << col << std::endl;

}
// el enum esta en tipos.h dentro de esta carpeta
void Controller::sender_mov_player(SDL_Keycode key) {

    Movement mov = Movement::NONE;
    if (key == SDLK_UP || key == SDLK_w) {
        mov = Movement::UP;
    } else if (key == SDLK_LEFT || key == SDLK_a) {
        mov = Movement::LEFT;
    } else if (key == SDLK_RIGHT || key == SDLK_d) {
        mov = Movement::RIGHT;
    } else if (key == SDLK_DOWN || key == SDLK_s) {
        mov = Movement::DOWN;
    }
    std::cout << static_cast<int>(mov) << std::endl;
}

void Controller::run() {}
