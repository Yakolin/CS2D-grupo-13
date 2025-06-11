#ifndef SHOPPIMNG_H
#define SHOPPIMNG_H
#include <iostream>
#include <map>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <SDL_video.h>

#include "../tipos.h"

#include "camera.h"
#include "gameConfig.h"
#include "manageTexture.h"
#include "player_command_types.h"
#include "renderizable.h"


class Shopping: public Renderizable {


private:
    GameConfig& config;
    Camera& camera;
    ManageTexture& manejador;
    //  std::vector<ShopItem> items;
    std::unordered_map<Weapon, ShopItem> items;
    int selectedIndex;
    SDL_Rect rect_shop;
    bool activa;
    SDL_Texture* texture_menu;
    Weapon weapon_selec;

    void load_items(const Weapon& clave, const std::string& name, const int& price,
                    const SDL_Rect& destRect, const std::string& descrpcion);

public:
    explicit Shopping(Camera& camera_reseiver, ManageTexture& manejador, GameConfig& config);

    Weapon get_wepon_selec();

    void activate_shop();

    bool get_activa() const;

    ~Shopping();

    void update(const std::vector<WeaponData>& data);

    WeaponCode calculate_selection(const int& mouse_x, const int& mouse_y);

    /*
    pre: render y texturas deben existir y el mapa no debe estar vacio.
    post:
    */
    void draw(SDL_Renderer& renderer) override;
};

#endif  // SHOPPIMNG_H
