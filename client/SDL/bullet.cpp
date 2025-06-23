
#include "bullet.h"

#include <iostream>


Bullet::Bullet(const Coordenada& start, const Coordenada& end, const int& width,
               const WeaponCode& code):
        current(start), end(end), width(width), code(code), start_time(SDL_GetTicks()) {}


void Bullet::calculate_values(SDL_Rect& destination_rect, double& angulo, SDL_Point& center,
                              const SDL_Point& p_init, const SDL_Point& p_end) {

    double dx = p_end.x - p_init.x;
    double dy = p_end.y - p_init.y;
    angulo = atan2(dy, dx) * 180.0 / M_PI;
    int longitud = static_cast<int>(sqrt(dx * dx + dy * dy));
    destination_rect.x = static_cast<int>(p_init.x - camera.x);
    destination_rect.y =
            static_cast<int>(p_init.y - longitud - camera.y);  // verticalmente centrado
    destination_rect.w = longitud;
    destination_rect.h = longitud * 2;
    center = {0, longitud};
}

void Bullet::draw(SDL_Renderer& renderer, SDL_Texture* texture,SDL_Rect destination_rect,double angulo,  SDL_Point center){
    SDL_RenderCopyEx(&renderer, texture, nullptr, &destination_rect, angulo, &center,SDL_FLIP_NONE);
}
void Bullet::draw(SDL_Renderer& renderer) {

    if (code == WeaponCode::M3) {
        SDL_Point p_init = {static_cast<int>(current.x), static_cast<int>(current.y)};
        SDL_Point p_end = {static_cast<int>(end.x), static_cast<int>(end.y)};

        double angulo = 0;
        SDL_Point center;
        SDL_Rect destination_rect;
        calculate_values(destination_rect, angulo, center, p_init, p_end);
        SDL_Texture* texture = crear_cono(&renderer, p_init, p_end, 45, 1);
        draw(renderer, texture, destination_rect, angulo, center);

    } else {
        SDL_RenderDrawLine(&renderer, static_cast<int>(current.x - camera.x),
                           static_cast<int>(current.y - camera.y),
                           static_cast<int>(end.x - camera.x), static_cast<int>(end.y - camera.y));
    }
}

SDL_Texture* Bullet::crear_cono(SDL_Renderer* renderer, SDL_Point p_inicial, SDL_Point p_final,
                                double apertura_grados = 60, int paso = 1) {

    double dx = p_final.x - p_inicial.x;
    double dy = p_final.y - p_inicial.y;
    double longitud = sqrt(dx * dx + dy * dy);

    int ancho = (int)longitud;
    int alto = (int)(longitud * 2);

    SDL_Texture* textura = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                             SDL_TEXTUREACCESS_TARGET, ancho, alto);
    if (!textura)
        return nullptr;
    SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);
    SDL_Texture* target_original = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, textura);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_Point centro_local = {0, alto / 2};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    double apertura_rad = apertura_grados * M_PI / 180.0;
    for (double a = -apertura_rad / 2; a <= apertura_rad / 2; a += paso * M_PI / 180.0) {
        int x = centro_local.x + cos(a) * longitud;
        int y = centro_local.y + sin(a) * longitud;
        SDL_RenderDrawLine(renderer, centro_local.x, centro_local.y, x, y);
    }
    SDL_SetRenderTarget(renderer, target_original);
    return textura;
}

float Bullet::get_currentX() { return current.x; }
float Bullet::get_currenty() { return current.y; }
float Bullet::get_endX() { return end.x; }
float Bullet::get_endy() { return end.y; }

bool Bullet::finalizado() { return SDL_GetTicks() - start_time > end_time; }
