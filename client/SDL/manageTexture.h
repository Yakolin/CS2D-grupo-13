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

class ManageTexture {
public:

    explicit ManageTexture(SDL_Renderer* renderer);

    bool load(const Object& id, const std::string& filePath, SDL_Renderer* renderer);

    void fillTriangle(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, int x2, int y2);

    SDL_Texture* create_stencil(const int& ancho, const int& alto, const float& angle,
                                const float& apertura);

    bool load_weapons(const Weapon& id, const std::string& filePath, SDL_Renderer* renderer);

    SDL_Texture* get_weapon(const Weapon& id) const;

    bool load_texture_text(const TextView& id,TTF_Font* fuente, SDL_Color& color,const std::string& text, SDL_Renderer* renderer);

    SDL_Texture * get_texture_text(const TextView & id) const;

    SDL_Rect get_rect(const TextView& id) const;

    SDL_Texture* get(const Object& id) const;
    
    void remove(const TextView& id);
    
    void clear();

private:
    SDL_Renderer* renderer;
    std::unordered_map<Object, SDL_Texture*> textures;
    std::unordered_map<TextView, TextureData> textures_text;
    std::unordered_map<Weapon,SDL_Texture*> textures_weapons;

};

#endif
