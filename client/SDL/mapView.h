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
#include "../../common/utility.h"
#include "../tipos.h"
#include "gameConfig.h"
#include "playerView.h"
#include "renderizable.h"


class MapView: public Renderizable {

public:
    explicit MapView(const std::vector<Position> walls, Camera* camera_reseiver, ManageTexture* manejador,GameConfig& config);
    ~MapView();

    /*
    pre: render y texturas deben existir y el mapa no debe estar vacio.
    post:recorre el mapa y dibuja texturas de 32x32 pixeles
    */
    void draw(SDL_Renderer& renderer) override;

    std::vector<std::vector<char>> cargar_coordenadas(const std::vector<Position> walls);

    void update_map_dimensions();
    int getMapWidth();
    int getMapHeight();


private:
    GameConfig& config;
    std::vector<std::vector<char>> mapa;
    int width_map;
    int height_map;
    Camera* camera;
    ManageTexture* manejador;
    std::map<char, Object> ids;
    void update_limites(Coordenada& pos_start, Coordenada& pos_end);
};

#endif  // MAPVIEW_H
