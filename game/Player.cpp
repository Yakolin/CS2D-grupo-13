#include "Player.h"
//  "Copyright 2025 Yaco Santamarina"
void Player::move(Vector2&& direction) { position += direction; }

void Player::fire_weapon_equiped(const Vector2& mouse_pointer) {
    Vector2 direction = mouse_pointer - position;
    direction.normalize();
    equipement.current_weapon->fire(position, direction);
}

void Player::get_damage(float damage) { health -= damage; }
// void Player::change_weapon_equiped() {}
