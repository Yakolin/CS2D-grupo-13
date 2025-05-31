#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <iostream>
#include <map>
#include <vector>
#include "camera.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>

#include "../tipos.h"

#include "playerView.h"
#include "renderizable.h"


class MapView: public Renderizable {

public:
    explicit MapView(const std::vector<std::vector<char>>& mapa, const int& width,
                     const int& height, Camera* camera_reseiver, ManageTexture* manejador);
    ~MapView();

    /*
    pre: render y texturas deben existir y el mapa no debe estar vacio.
    post:recorre el mapa y dibuja texturas de 32x32 pixeles
    */
    void draw(SDL_Renderer& renderer) override;
    int getMapWidth();
    int getMapHeight();


private:
    int width;
    int height;
    std::vector<std::vector<char>> mapa;
    int width_map;
    int height_map;
    //SDL_Rect* camera;
    Camera* camera;
    ManageTexture* manejador;
    std::map<char, Object> ids;
};

#endif  // MAPVIEW_H
