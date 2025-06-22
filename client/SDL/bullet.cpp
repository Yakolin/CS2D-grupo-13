
#include "bullet.h"

#include <iostream>


Bullet::Bullet(const Coordenada& start, const Coordenada& end, int width, SDL_Texture* texture):
        current(start), end(end), width(width), texture(texture), start_time(SDL_GetTicks()) {}


void Bullet::draw(SDL_Renderer& renderer) {
    SDL_RenderDrawLine(&renderer, static_cast<int>(current.x - camera.x),
                       static_cast<int>(current.y - camera.y), static_cast<int>(end.x - camera.x),
                       static_cast<int>(end.y - camera.y));
}


float Bullet::get_currentX() { return current.x; }
float Bullet::get_currenty() { return current.y; }
float Bullet::get_endX() { return end.x; }
float Bullet::get_endy() { return end.y; }

bool Bullet::finalizado() { return SDL_GetTicks() - start_time > end_time; }
