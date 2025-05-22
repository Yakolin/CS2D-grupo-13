#include "Player.h"
//  "Copyright 2025 Yaco Santamarina"
void Player::move(Vector2&& direction) { position += direction; }

void Player::fire_weapon_equiped(Map& map, const Vector2& mouse_pointer) {
    Vector2 direction = mouse_pointer - position;
    // direction.normalize(); Hay que revisar esta funcion dado el problema de los uint16_t en Vector2
    // Esto deberia de ser en realidad current weapon pero no se como hacerlo
    if (equipement.secondary)
        equipement.secondary->fire(map, id, position, direction);
    // Exception)?
}
void Player::get_damage(uint8_t damage) { health -= damage; }
// void Player::change_weapon_equiped() {}
