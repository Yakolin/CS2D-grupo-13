
#include "bomb.h"

const int UN_SEGUNDO = 100;
Bomb::Bomb(int x, int y, Camera& camera_reseiver, ManageTexture& manejador, GameConfig& config):
        config(config),
        camera(camera_reseiver),
        manejador(manejador),
        texture_bomb(manejador.get_weapon(WeaponCode::BOMB)),
        texture_explosion(manejador.get(Object::EXPLOSION)),
        width_img(),
        height_img(),
        item_sprite({0, 0}),
        pos_bomb(),
        angle(0),
        last_frame_time(SDL_GetTicks()),
        state(BombState::DROPPED),
        x(x),
        y(y) {
    manejador.calculate_dimensions(width_img, height_img, Object::EXPLOSION);
}

void Bomb::set_pos(int& new_x, int& new_y) {
    this->x = new_x;
    this->y = new_y;
}

void Bomb::update_bomb(const BombImage& bombImg) {

    destination_rect.x =
            (static_cast<int>(bombImg.position.x) * config.get_tile_width()) - camera.getX();
    destination_rect.y =
            (static_cast<int>(bombImg.position.y) * config.get_tile_height()) - camera.getY();
    state = bombImg.state;
}


void Bomb::draw_dropped(SDL_Renderer& renderer) {
    destination_rect.w = config.get_tile_width();
    destination_rect.h = config.get_tile_height();
    SDL_RenderCopyEx(&renderer, texture_bomb, nullptr, &destination_rect, angle, nullptr,
                     SDL_FLIP_NONE);
}
void Bomb::draw_activate(SDL_Renderer& renderer) {
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
    SDL_RenderCopyEx(&renderer, texture_explosion, &origin_rect, &destination_rect, angle, nullptr,
                     SDL_FLIP_NONE);
}

void Bomb::draw(SDL_Renderer& renderer) {

    switch (state) {
        case BombState::EQUIPED:
            break;
        case BombState::DROPPED:
            draw_dropped(renderer);
            break;
        case BombState::ACTIVATED:
            draw_dropped(renderer);
            break;
        case BombState::DESACTIVATED:
            draw_dropped(renderer);
            break;
        case BombState::EXPLOTED:
            draw_activate(renderer);
            break;
        default:
            break;
    }
}

bool Bomb::explosion_finished() { return item_sprite.y == 5; }
Bomb::~Bomb() {}