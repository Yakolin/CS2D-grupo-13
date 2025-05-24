#include "Player.h"

#include <memory>
    //  "Copyright 2025 Yaco Santamarina"
    // void Player::move(Position&& direction) { position += direction; }

void Player::fire_weapon_equiped(Map& map, Position& position, Position& direction) {
    // direction.normalize(); Hay que revisar esta funcion dado el problema de los uint16_t en
    // Position Esto deberia de ser en realidad current weapon pero no se como hacerlo
    if (equipement.secondary)
        equipement.secondary->set_on_action(map.damage_colliders, id, position, direction);
    // Exception)?
}
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
