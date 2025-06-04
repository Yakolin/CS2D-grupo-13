#include "Player.h"

#include <memory>

void Player::damage(uint8_t damage) {
    if (damage > health)
        health = 0;
    health -= damage;
}

bool Player::dead() { return health == 0; }

void Player::reset(bool full_reset) {
    if (full_reset || health == 0) {
        equipment.reset_equipment();
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
void Player::reload() { this->equipment.reload(); }

void Player::shoot(const coordinate_t& mouse_x, const coordinate_t& mouse_y) {
    Position position(mouse_x, mouse_y);
    this->equipment.shoot(this->id, position);
}

PlayerImage Player::get_player_image(const Position& position, Team team) {
    return PlayerImage(id, Position(position.x, position.y), health, points,
                       std::move(equipment.get_weapons_image()), team);
}
void Player::buy_weapon(const WeaponCode& weapon_code) {
    equipment.buy_weapon_by_code(weapon_code, money);
}

void Player::drop() { this->equipment.drop_weapon(this->id); }

void Player::equip(const EquipType& equip_type) { this->equipment.change_weapon(equip_type); }
