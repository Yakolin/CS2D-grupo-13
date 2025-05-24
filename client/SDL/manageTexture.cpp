/*Función	Descripción
load(filePath, id)	Carga una textura desde disco y la guarda con un ID.
get(id)	Devuelve la textura previamente cargada con ese ID.
unload(id) (opcional)	Libera memoria de una textura si ya no se necesita.
clear() (opcional)	Elimina todas las texturas (por ejemplo, al cerrar el juego).
*/
#include "manageTexture.h"

#include <iostream>

bool ManageTexture::load(const Objet& id, const std::string& filePath, SDL_Renderer* renderer) {

    SDL_Surface* stoneSurface = IMG_Load(filePath.c_str());
    if (!stoneSurface) {
        std::cerr << "Error cargando imagen de piedra: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture* tiles = SDL_CreateTextureFromSurface(renderer, stoneSurface);
    if (!tiles) {
        std::cerr << "Error creando textura de piedra: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_FreeSurface(stoneSurface);

    textures[id] = tiles;
    /*for (const auto& par : textures) {
        std::cout << "Clave (valor numérico): " << static_cast<int>(par.first)
              << " | Valor (puntero SDL_Texture*): " << par.second << std::endl;
    }*/
    return true;
}

SDL_Texture* ManageTexture::get(const Objet& id) const {
    auto it = textures.find(id);
    if (it != textures.end()) {
        return it->second;
    }
    return nullptr;
}

void ManageTexture::remove(const Objet& id) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        SDL_DestroyTexture(it->second);
        textures.erase(it);
    }
}

void ManageTexture::clear() {
    for (auto& pair: textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
}
