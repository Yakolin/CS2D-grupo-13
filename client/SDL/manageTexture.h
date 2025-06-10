#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <string>
#include <unordered_map>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../tipos.h"
#include <array>
#include <vector>
#include <iostream>
#include <map>
#include <stdexcept>
#include <sstream>
#include <SDL2/SDL2_gfxPrimitives.h>
class ManageTexture {
public:

    
    SDL_Texture* reder_menu_texture(const  std::unordered_map<Weapon, ShopItem>& items,const SDL_Rect& menu_rect ,TTF_Font* fontt);
    
    explicit ManageTexture(SDL_Renderer* renderer);

    void drawHealthBar( int x, int y, int width, int height, float healthPercent);

    void load(const Object& id, const std::string& filePath);

    void fillTriangle(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, int x2, int y2);

    SDL_Texture* create_stencil(const int& ancho, const int& alto, const float& angle,
                                const float& apertura);

    bool load_weapons(const Weapon& id, const std::string& filePath, SDL_Renderer* renderer);

    SDL_Texture* get_weapon(const Weapon& id) const;

    bool load_texture_text(const TextView& id,TTF_Font* fuente, SDL_Color& color,const std::string& text);

    SDL_Texture * get_texture_text(const TextView & id) const;

    SDL_Rect get_rect(const TextView& id) const;

    SDL_Texture* get(const Object& id) const;
    
    void remove(const TextView& id);
    
    void clear();

    void calculate_dimensions(int& width_img, int& height_img,const Object& clave) ;


private:
    SDL_Renderer* renderer;
    std::unordered_map<Object, SDL_Texture*> textures;
    std::unordered_map<TextView, TextureData> textures_text;
    std::unordered_map<Weapon,SDL_Texture*> textures_weapons;
    std::unordered_map<Color, SDL_Color> colores;

    TTF_Font *get_font_menu();

    void render_text(const SDL_Rect& rect,const std::string& text,const  SDL_Color& color, TTF_Font* font);
};

#endif
