#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../tipos.h"

class ManageTexture {
public:
    bool load(const Object& id, const std::string& filePath, SDL_Renderer* renderer);

    bool load_weapons(const Weapon& id, const std::string& filePath, SDL_Renderer* renderer);

    bool load_texture_text(const TextView& id,TTF_Font* fuente, SDL_Color& color,const std::string& text, SDL_Renderer* renderer);

    SDL_Texture * get_texture_text(const TextView & id) const;

    SDL_Rect get_rect(const TextView& id) const;

    SDL_Texture* get(const Object& id) const;
    
    void remove(const TextView& id);
    
    void clear();

    void  objectToString() ;

private:
    std::unordered_map<Object, SDL_Texture*> textures;
    std::unordered_map<TextView, TextureData> textures_text;
    std::unordered_map<Weapon,SDL_Texture*> textures_weapons;

};

#endif
