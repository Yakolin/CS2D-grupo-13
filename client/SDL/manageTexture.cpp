#include "manageTexture.h"
#include <iostream>
#include <stdexcept>

bool ManageTexture::load(const Object& id, const std::string& filePath, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Error cargando imagen: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Error creando textura: " << SDL_GetError() << std::endl;
        return false;
    }

    // Guardamos solo la textura para imágenes normales
    textures[id] = texture;
    return true;
}

bool ManageTexture::load_texture_text(const TextView& id, TTF_Font* fuente, SDL_Color& color, const std::string& text, SDL_Renderer* renderer) {
    
    
    SDL_Surface* surface = TTF_RenderText_Blended(fuente, text.c_str(), color);
    if (!surface) {
        throw std::runtime_error("Error al crear superficie de texto: " + std::string(TTF_GetError()));
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        throw std::runtime_error("Error al crear textura de texto: " + std::string(SDL_GetError()));
    }

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); // para habilitar la transparencia
    SDL_SetTextureAlphaMod(texture, 128);
        
    TextureData data;
    data.texture = texture;
    data.width = surface->w;
    data.height = surface->h;

    SDL_FreeSurface(surface);

    // Guardamos en el mapa de texturas de texto
    textures_text[id] = data;
    return true;
}

SDL_Texture* ManageTexture::get_texture_text(const TextView& id) const {

    auto it = textures_text.find(id);
    if (it != textures_text.end()) {
        return it->second.texture;
    }
    return nullptr;
}

SDL_Rect ManageTexture::get_rect(const TextView& id) const {

    auto it_text = textures_text.find(id);
    if (it_text != textures_text.end()) {
        return SDL_Rect{0, 0, it_text->second.width, it_text->second.height};
    }
    return SDL_Rect{0, 0, 0, 0};
}

SDL_Texture* ManageTexture::get(const Object& id) const {

    auto it = textures.find(id);
    if (it != textures.end()) {
        return it->second;
    }
    return nullptr;
}

void ManageTexture::remove(const TextView& id) {
    auto it_tex = textures_text.find(id);
    if (it_tex != textures_text.end()) {
        SDL_DestroyTexture(it_tex->second.texture);
        textures_text.erase(it_tex);
    }
}

void ManageTexture::clear() {
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();

    for (auto& pair : textures_text) {
        SDL_DestroyTexture(pair.second.texture);
    }
    textures_text.clear();
}
void  ManageTexture::objectToString() {

    std::cout << "=== Claves en textures ===\n";
    for (const auto& pair : textures) {
        std::cout << static_cast<int>(pair.first) << '\n';
    }
}
