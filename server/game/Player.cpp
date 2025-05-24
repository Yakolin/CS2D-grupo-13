#include "Player.h"

#include <memory>
//  "Copyright 2025 Yaco Santamarina"
// void Player::move(Position&& direction) { position += direction; }
void Player::get_damage(uint8_t damage) { health -= damage; }
// void Player::change_weapon_equiped() {}

void Player::reset() {
    if (health == 0) {
        equipement.primary = nullptr;
        equipement.secondary = nullptr;
        equipement.secondary = std::make_unique<Glock>();
    }
    health = 100;
}