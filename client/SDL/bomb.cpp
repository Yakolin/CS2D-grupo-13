
#include "bomb.h"


Bomb::Bomb(PlayerView& player, Camera& camera_reseiver, ManageTexture& manejador,
           GameConfig& config):
        player_actual(player),
        camera(camera_reseiver),
        manejador(manejador),
        config(config),
        width_img(),
        height_img(),
        item_sprite({0, 0}),
        pos_bomb(),
        activada(false) {
    manejador.calculate_dimensions(width_img, height_img, Weapon::BOMB);
    update();
}

bool Bomb::get_activate() const { return activada; }

void Bomb::update() {

    int offsetX = 20;
    int offsetY = 2;
    this->angle = player_actual.getAnglePlayer();

    destination_rect.x = static_cast<int>(player_actual.getXActual() + offsetX) - camera.getX();
    destination_rect.y = static_cast<int>(player_actual.getYActual() + offsetY) - camera.getY();
    destination_rect.w = 15;
    destination_rect.h = 15;
}
void Bomb::draw(SDL_Renderer& renderer) {
    if (activada) {
        origin_rect = {(item_sprite.x * width_img), (item_sprite.y * height_img), (width_img / 2),
                       (height_img / 3)};
        if (item_sprite.y < 5) {
            item_sprite.y++;
        } else {
            item_sprite.y = 0;
            item_sprite.x++;
        }

    } else {
        origin_rect = nullptr;
    }
    SDL_RenderCopyEx(&renderer, tiles_player, origin_rect, &destination_rect, angle, nullptr,
                     SDL_FLIP_NONE);
}


Bomb::~Bomb() {}