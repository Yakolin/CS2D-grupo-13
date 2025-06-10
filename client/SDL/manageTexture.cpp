#include "manageTexture.h"

#include <iostream>
#include <stdexcept>

#include <SDL2/SDL2_gfxPrimitives.h>
ManageTexture::ManageTexture(SDL_Renderer* renderer): renderer(renderer) {}


void ManageTexture::calculate_dimensions(int& width_img, int& height_img, const Weapon& clave) {

    SDL_Texture* texture = get_weapon(clave);
    if (texture) {
        std::cerr << "Error: No se pudo cargar la textura ." << std::endl;
        return;
    }
    SDL_QueryTexture(texture, nullptr, nullptr, &width_img, &height_img);
}

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

    textures[id] = texture;
    return true;
}


void ManageTexture::fillTriangle(SDL_Renderer* renderer, int x0, int y0, int x1, int y1, int x2,
                                 int y2) {
    // Ordenar los puntos por Y
    if (y1 < y0) {
        std::swap(y0, y1);
        std::swap(x0, x1);
    }
    if (y2 < y0) {
        std::swap(y0, y2);
        std::swap(x0, x2);
    }
    if (y2 < y1) {
        std::swap(y1, y2);
        std::swap(x1, x2);
    }

    auto drawScanline = [&](int y, int xa, int xb) {
        if (xa > xb)
            std::swap(xa, xb);
        SDL_RenderDrawLine(renderer, xa, y, xb, y);
    };

    for (int y = y0; y <= y2; ++y) {
        bool second_half = y > y1 || y1 == y0;
        int segment_height = second_half ? y2 - y1 : y1 - y0;
        float alpha = (float)(y - y0) / (y2 - y0);
        float beta = (float)(y - (second_half ? y1 : y0)) / segment_height;

        int ax = x0 + (x2 - x0) * alpha;
        int bx = second_half ? x1 + (x2 - x1) * beta : x0 + (x1 - x0) * beta;

        drawScanline(y, ax, bx);
    }
}

std::array<SDL_Point, 4> calculo(const int& lado, const int& angle, const int& apertura) {
    int cx = lado / 2;
    int cy = lado / 2;
    float radio = (lado / 2) * 0.9;  // 90% del máximo
    float angle_rad = angle * M_PI / 180.0f;
    float apertura_rad = apertura * M_PI / 180.0f;

    SDL_Point points[4];
    int x1 = static_cast<int>(cx + radio * cos(angle_rad - apertura_rad / 2));
    int y1 = static_cast<int>(cy + radio * sin(angle_rad - apertura_rad / 2));

    int x2 = static_cast<int>(cx + radio * cos(angle_rad + apertura_rad / 2));
    int y2 = static_cast<int>(cy + radio * sin(angle_rad + apertura_rad / 2));

    points[0] = {cx, cy};
    points[1] = {x1, y1};
    points[2] = {x2, y2};
    points[3] = points[0];

    return {points[0], points[1], points[2], points[3]};
}

SDL_Texture* ManageTexture::create_stencil(const int& ancho, const int& alto, const float& angle,
                                           const float& apertura) {

    int lado = ancho + alto;
    SDL_Texture* stencil = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                             SDL_TEXTUREACCESS_TARGET, lado, lado);
    if (!stencil) {
        throw std::runtime_error("Error: la textura stencil  no se cargó correctamente.");
    }
    SDL_Texture* old_target = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, stencil);
    std::array<SDL_Point, 4> points = calculo(lado, angle, apertura);

    // int radio_fondo = lado / 4;
    int radio_pequeno = 64;  // Ajusta este valor al tamaño deseado


    SDL_SetTextureBlendMode(stencil, SDL_BLENDMODE_BLEND);  // vuelve tui textura trasparente

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);  // 128 fondo simi trasparente negro
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_RenderClear(renderer);


    // filledCircleRGBA(renderer, points[0].x, points[0].y, radio_fondo, 0, 0, 0, 128);
    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    filledCircleRGBA(renderer, points[0].x, points[0].y, radio_pequeno, 0, 0, 0, 0);


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    fillTriangle(renderer, points[0].x, points[0].y, points[1].x, points[1].y, points[2].x,
                 points[2].y);


    SDL_SetRenderTarget(renderer, old_target);

    return stencil;
}


bool ManageTexture::load_weapons(const Weapon& id, const std::string& filePath,
                                 SDL_Renderer* renderer) {

    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Error cargando imagen: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Error creando textura de weapon: " << SDL_GetError() << std::endl;
        return false;
    }

    textures_weapons[id] = texture;
    return true;
}
SDL_Texture* ManageTexture::get_weapon(const Weapon& id) const {
    auto it = textures_weapons.find(id);
    if (it != textures_weapons.end()) {
        return it->second;
    }
    return nullptr;
}

bool ManageTexture::load_texture_text(const TextView& id, TTF_Font* fuente, SDL_Color& color,
                                      const std::string& text, SDL_Renderer* renderer) {


    SDL_Surface* surface = TTF_RenderText_Blended(fuente, text.c_str(), color);
    if (!surface) {
        throw std::runtime_error("Error al crear superficie de texto: " +
                                 std::string(TTF_GetError()));
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        throw std::runtime_error("Error al crear textura de texto: " + std::string(SDL_GetError()));
    }

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);  // para habilitar la transparencia
    SDL_SetTextureAlphaMod(texture, 128);

    TextureData data;
    data.texture = texture;
    data.width = surface->w;
    data.height = surface->h;

    SDL_FreeSurface(surface);
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
    for (auto& pair: textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();

    for (auto& pair: textures_text) {
        SDL_DestroyTexture(pair.second.texture);
    }
    textures_text.clear();
}
/*void  ManageTexture::objectToString() {

    std::cout << "=== Claves en textures ===\n";
    for (const auto& pair : textures) {
        std::cout << static_cast<int>(pair.first) << '\n';
    }
}
*/

/*
SDL_Texture* ManageTexture::create_stencil(const int& ancho, const int& alto,const  float& angle,
const float& apertura) {

    std::cout << "Llamado a create_stencil con los siguientes
valores:-----------------------------\n"; std::cout << "Ancho: " << ancho << "\n"; std::cout <<
"Alto: " << alto << "\n"; std::cout << "Ángulo: " << angle << "\n"; std::cout << "Apertura: " <<
apertura << "\n"; int lado = ancho+alto; std::cout << "lado: " << lado << "\n";


    SDL_Texture* stencil = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
SDL_TEXTUREACCESS_TARGET, lado, lado); if (!stencil) { throw std::runtime_error("Error: la textura
stencil  no se cargó correctamente.");
    }

    SDL_SetTextureBlendMode(stencil, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(stencil, 128);

    SDL_Texture* old_target = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, stencil);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    int cx = lado / 2;
    int cy = lado / 2;
    float radio = lado / 2;
    float angle_rad = angle * M_PI / 180.0f;
    float apertura_rad = apertura * M_PI / 180.0f;
    SDL_Point points[4];

    points[0] = {cx, cy};
    points[1] = {
        static_cast<int>(std::round(cx + radio * cos(angle_rad - apertura_rad / 2))),
        static_cast<int>(std::round(cy + radio * sin(angle_rad - apertura_rad / 2)))
    };
    points[2] = {
        static_cast<int>(std::round(cx + radio * cos(angle_rad + apertura_rad / 2))),
        static_cast<int>(std::round(cy + radio * sin(angle_rad + apertura_rad / 2)))
    };
    points[3] = points[0];

  //  SDL_RenderDrawLines(renderer, points, 4);

    for (int i = 0; i <= 100; ++i) {
        float t = i / 100.0f;
        int x = static_cast<int>(points[1].x + t * (points[2].x - points[1].x));
        int y = static_cast<int>(points[1].y + t * (points[2].y - points[1].y));
        SDL_RenderDrawLine(renderer, points[0].x, points[0].y, x, y);
    }

    SDL_SetRenderTarget(renderer, old_target);

    return stencil;
}*/