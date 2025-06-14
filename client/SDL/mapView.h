#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <iostream>
#include <map>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>

#include "../../common/utility.h"
#include "../../common/game_info.h"
#include "../tipos.h"

#include "camera.h"
#include "gameConfig.h"
#include "playerView.h"
#include "renderizable.h"


class MapView: public Renderizable {

public:
    explicit MapView(const MapInfo& info, Camera* camera_reseiver,
                     ManageTexture* manejador, GameConfig& config);
    ~MapView();

    /*
    pre: render y texturas deben existir y el mapa no debe estar vacio.
    post:recorre el mapa y dibuja texturas de 32x32 pixeles
    */
    void draw(SDL_Renderer& renderer) override;

    std::vector<std::vector<char>> cargar_coordenadas(const std::vector<Position> walls, const char& piso, const int& max_fil, const int& max_col,const char& objet);

    std::vector<std::vector<char>> completar_mapa(const MapInfo& info_map);

    void update_map_dimensions();
    void render_objet(SDL_Renderer& renderer);
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
    std::vector<Position> libres;

    void update_limites(Coordenada& pos_start, Coordenada& pos_end);

    void free_positions( std::vector<std::vector<char>> mapa, const char& piso,const char& wall, const int& max_fil, const int& max_col);

    void load_trees(int& size_objet);
};

#endif  // MAPVIEW_H
