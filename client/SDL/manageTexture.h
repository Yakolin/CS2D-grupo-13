#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <array>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../../common/game_info.h"
#include "../../common/player_command_types.h"
#include "../tipos.h"
class ManageTexture {
public:
    SDL_Texture* render_menu_texture(const std::unordered_map<WeaponCode, ShopItem>& items, const SDL_Rect& menu_rect,
        TTF_Font* font);

    explicit ManageTexture(SDL_Renderer* renderer);

    void drawHealthBar(int x, int y, int width, int height, float healthPercent);

    void load(const Object& id, const std::string& filePath);

    void load_skins_tt(const TerroristSkin& id, const std::string& filePath);

    void load_skins_ct(const CounterTerroristSkin& id, const std::string& filePath);

    SDL_Texture* get_texture_ct(const CounterTerroristSkin& id) const;

    SDL_Texture* get_texture_tt(const TerroristSkin& id) const;

    void fillTriangle(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, int x2, int y2);

    SDL_Texture* create_stencil(const int& ancho, const int& alto, const float& angle,
                                const float& apertura,const int& intensity);

    bool load_weapons(const WeaponCode& id, const std::string& filePath, SDL_Renderer* renderer);

    SDL_Texture* get_weapon(const WeaponCode& id) const;

    bool load_texture_text(const TextView& id, TTF_Font* fuente, SDL_Color& color,
                           const std::string& text);

    SDL_Texture* get_texture_text(const TextView& id) const;

    SDL_Rect get_rect(const TextView& id) const;

    SDL_Texture* get(const Object& id) const;

    void remove(const TextView& id);

    void clear();

    void calculate_dimensions(int& width_img, int& height_img, const Object& clave);


private:
    SDL_Renderer* renderer;
    std::unordered_map<Object, SDL_Texture*> textures;
    std::unordered_map<TextView, TextureData> textures_text;
    std::unordered_map<WeaponCode, SDL_Texture*> textures_weapons;
    std::unordered_map<Color, SDL_Color> colores;
    std::unordered_map<CounterTerroristSkin, SDL_Texture*> texture_skin_ct;
    std::unordered_map<TerroristSkin, SDL_Texture*> texture_skin_tt;

    TTF_Font* get_font_menu();

    void render_text(const SDL_Rect& rect, const std::string& text, const SDL_Color& color,
                     TTF_Font* font);
};

#endif
