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

#include "../../common/player_command_types.h"
#include "../tipos.h"

#include "camera.h"
#include "gameConfig.h"
#include "manageTexture.h"
#include "renderizable.h"


class Shopping: public Renderizable {


private:
    GameConfig& config;
    Camera& camera;
    ManageTexture& manejador;
    //  std::vector<ShopItem> items;
    std::unordered_map<WeaponCode, ShopItem> items;
    int selectedIndex;
    SDL_Rect rect_shop;
    bool activa;
    SDL_Texture* texture_menu;
    WeaponCode weapon_selec;

    void code_to_info_weapon(const WeaponCode& code, std::string& name, std::string& descripcion);

    void load_items(const WeaponInfo& clave, const SDL_Rect& destRect);

public:
    explicit Shopping(Camera& camera_reseiver, ManageTexture& manejador, GameConfig& config);

    void set_weapons_purchasables(const std::vector<WeaponInfo>& weapons_purchasables);

    WeaponCode get_wepon_selec();
    void desactivate_shop();

    void activate_shop();

    bool get_activa() const;

    ~Shopping();

    WeaponCode calculate_selection(const int& mouse_x, const int& mouse_y);

    /*
    pre: render y texturas deben existir y el mapa no debe estar vacio.
    post:
    */
    void draw(SDL_Renderer& renderer) override;
};

#endif  // SHOPPIMNG_H
