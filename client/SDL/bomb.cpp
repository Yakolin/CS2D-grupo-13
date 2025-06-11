
#include "bomb.h"

const int UN_SEGUNDO = 100;
Bomb::Bomb(int x, int y, Camera& camera_reseiver, ManageTexture& manejador, GameConfig& config):
        config(config),
        camera(camera_reseiver),
        manejador(manejador),
        texture_bomb(manejador.get_weapon(Weapon::BOMB)),
        texture_explosion(manejador.get(Object::EXPLOSION)),
        width_img(),
        height_img(),
        item_sprite({0, 0}),
        pos_bomb(),
        activada(false),
        last_frame_time(SDL_GetTicks()) {
    manejador.calculate_dimensions(width_img, height_img, Object::EXPLOSION);
    update();
}

bool Bomb::get_activate() const { return activada; }

void Bomb::activate() { this->activada = true; }

void Bomb::update() {

    int offsetX = 20;
    int offsetY = 2;
    this->angle = player_actual->getAnglePlayer();

    destination_rect.x = static_cast<int>(player_actual->getXActual() + offsetX) - camera.getX();
    destination_rect.y = static_cast<int>(player_actual->getYActual() + offsetY) - camera.getY();
    destination_rect.w = 15;
    destination_rect.h = 15;
}

void Bomb::draw(SDL_Renderer& renderer) {
    // std::cout << "activada"<< static_cast<int>(activada)<< std::endl;
    if (activada) {
        Uint32 now = SDL_GetTicks();

        if (now - last_frame_time >= UN_SEGUNDO) {
            last_frame_time = now;
            if (item_sprite.x < 4) {
                item_sprite.x++;
            } else {
                item_sprite.x = 0;
                if (item_sprite.y < 4) {
                    item_sprite.y++;
                } else {
                    activada = false;  // Fin de la animación
                }
            }
        }
        destination_rect.w = config.get_tile_width() * 5;
        destination_rect.h = config.get_tile_height() * 5;
        origin_rect = {(item_sprite.x * width_img / 5), (item_sprite.y * height_img / 5),
                       (width_img / 5), (height_img / 5)};
        SDL_RenderCopyEx(&renderer, texture_explosion, &origin_rect, &destination_rect, angle,
                         nullptr, SDL_FLIP_NONE);
    } else {
        SDL_RenderCopyEx(&renderer, texture_bomb, nullptr, &destination_rect, angle, nullptr,
                         SDL_FLIP_NONE);
    }
}

bool Bomb::explosion_finished() { return item_sprite.y == 5; }
Bomb::~Bomb() {}