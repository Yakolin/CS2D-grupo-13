#include "Player.h"

#include <memory>
//  "Copyright 2025 Yaco Santamarina"
// void Player::move(Position&& direction) { position += direction; }
void Player::damage(uint8_t damage) { health -= damage; }
// void Player::change_weapon_equiped() {}

void Player::reset(bool full_reset) {
    if (full_reset || health == 0) {
        equipement.reset_equipement();
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
void Player::reload() {
    // Aca no es la secondary igual
    equipement.secondary->reload();
}
void Player::shoot(const coordinate_t& mouse_x, const coordinate_t& mouse_y) {
    Position direction(mouse_x, mouse_y);
    equipement.secondary->set_on_action(spawneable_zone, id, direction);
}

PlayerImage Player::get_player_image(const Position& position) {
    return PlayerImage(id, Position(position.x, position.y), health, points,
                       std::move(equipement.get_weapons_image()));
}
void Player::buy_weapon(const WeaponCode& weapon_code) {
    equipement.buy_weapon_by_code(weapon_code, money);
}
