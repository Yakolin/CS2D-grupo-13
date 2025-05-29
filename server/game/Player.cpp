#include "Player.h"

#include <memory>
//  "Copyright 2025 Yaco Santamarina"
// void Player::move(Position&& direction) { position += direction; }
void Player::damage(uint8_t damage) { health -= damage; }
// void Player::change_weapon_equiped() {}

void Player::reset() {
    if (health == 0) {
        equipement.primary = nullptr;
        equipement.secondary = nullptr;
        equipement.secondary = std::make_unique<Glock>();
    }
    health = 100;
}
void Player::move(const MoveType& move_type) {
    switch (move_type) {
        case MoveType::RIGHT:
            game_zone.move(id, Position(1, 0));
            break;
        case MoveType::LEFT:
            game_zone.move(id, Position(-1, 0));
            break;
        case MoveType::UP:
            game_zone.move(id, Position(0, 1));
            break;
        case MoveType::DOWN:
            game_zone.move(id, Position(0, -1));
            break;
    }
}
