#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <iostream>
#include "tipos.h"
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <iostream>
#include <array>
#include <SDL_image.h>


class MapView  {

public:
    explicit MapView();
    ~MapView();
    void start_game();
    bool cargarTexturaFondo(SDL_Renderer* renderer);
    

private:
    SDL_Texture* backgroundTexture;
    SDL_Window* ventana ;
    SDL_Renderer* renderer ;
    std::string wall;
    std::string stone ;
    std::string water;
    int fil;
    int col;
    std::array<std::array<int,16>,16> mapa;

};

#endif // MAPVIEW_H