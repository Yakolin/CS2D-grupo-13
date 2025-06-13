
#include "bullet.h"
#include <iostream>


Bullet::Bullet(const Coordenada& start,const Coordenada& end, SDL_Texture* texture)
:   current(start), 
    end(end),
    texture(texture) 
    {}



void Bullet::draw(SDL_Renderer& renderer){

    SDL_Rect bulletRect = {
        static_cast<int>(current.x * 32), 
        static_cast<int>(current.y* 32),
        15, 15};
     std::cout << "bulletRect -> x: " << bulletRect.x
              << ", y: " << bulletRect.y
              << ", w: " << bulletRect.w
              << ", h: " << bulletRect.h << std::endl;
    SDL_RenderCopyEx(&renderer, texture, nullptr, &bulletRect, 0, nullptr, SDL_FLIP_NONE);


}


float Bullet::get_currentX(){
    return current.x;
}
float Bullet::get_currenty(){return current.y;}
float Bullet::get_endX(){
    return end.x;
}
float Bullet::get_endy(){return end.y;}

void Bullet::updateBullet(float speed ) {
        float dx = end.x - current.x;
        float dy = end.y - current.y;
        float dist = sqrt(dx*dx + dy*dy);
        if (dist > speed) {
            current.x += (dx / dist) * speed;
            current.y += (dy / dist) * speed;
        } else {
            current.x = end.x;
            current.y = end.y;
        }
    }
