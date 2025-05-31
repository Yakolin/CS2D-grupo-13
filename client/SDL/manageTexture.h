#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../tipos.h"

class ManageTexture {
public:
    bool load(const Object& id, const std::string& filePath, SDL_Renderer* renderer);
    SDL_Texture* get(const Object& id) const;
    void remove(const Object& id);
    void clear();

private:
    std::unordered_map<Object, SDL_Texture*> textures;
};

#endif
