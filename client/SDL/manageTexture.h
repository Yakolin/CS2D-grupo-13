#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../tipos.h"

class ManageTexture {
public:
    bool load(const Objet& id, const std::string& filePath, SDL_Renderer* renderer);
    SDL_Texture* get(const Objet& id) const;
    void remove(const Objet& id);
    void clear();

private:
    std::unordered_map<Objet, SDL_Texture*> textures;
};

#endif
