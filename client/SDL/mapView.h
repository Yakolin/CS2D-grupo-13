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

#include "../../common/game_info.h"
#include "../../common/utility.h"
#include "../tipos.h"

#include "camera.h"
#include "gameConfig.h"
#include "playerView.h"
#include "renderizable.h"


class MapView: public Renderizable {


private:
    GameConfig& config;
    std::vector<std::vector<char>> mapa;
    int width_map;
    int height_map;
    Camera* camera;
    ManageTexture* manejador;
    std::map<char, Object> ids;
    std::vector<Position> libres;
    std::vector<Position> position_umbrellas;
    std::vector<WeaponView> weapon_dropped;
    std::unordered_map<Object, TextureInfo> zones;

    void update_limites(Coordenada& pos_start, Coordenada& pos_end);

    void free_positions(const int& max_fil, const int& max_col, char piso);

    void cargar_coordenadas(std::vector<std::vector<char>>& map, const std::vector<Position>& walls,
                            const char& objet);

    std::vector<std::vector<char>> completar_mapa(const MapInfo& info_map);


    TextureInfo load_zone_texture(const RectangleInfo& rectangle, const Object& zone,
                                  const SDL_Color& color);

    void draw_zone(const Object& clave, SDL_Renderer& renderer);

public:
    explicit MapView(const MapInfo& info, Camera* camera_reseiver, ManageTexture* manejador,
                     GameConfig& config);
    ~MapView();

    void update_map_dimensions();
    /*
    pre: render y texturas deben existir y el mapa no debe estar vacio.
    post:recorre el mapa y dibuja texturas de 32x32 pixeles
    */
    void draw(SDL_Renderer& renderer) override;

    void draw_weapon_dropped(SDL_Renderer& renderer);

    void render_objet(SDL_Renderer& renderer);

    std::unordered_map<Object, TextureInfo> load_zones(const MapInfo& info);

    int getMapWidth();

    int getMapHeight();

    void update_weapon_dropped(const std::vector<WeaponDropped>& dropped);

    void draw_zones(SDL_Renderer& renderer);
};

#endif  // MAPVIEW_H
