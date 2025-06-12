#include "Player.h"

#include <memory>
void Player::damage(uint8_t damage) {
    if (damage > health)
        health = 0;
    else
        health -= damage;
    if (is_dead())
        equipment.drop_all();
}
bool Player::is_dead() { return health == 0; }

void Player::reset(bool full_reset) {
    if (full_reset || health == 0) {
        equipment.reset_equipment();
    }
    health = config.health;
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
    std::cout << "Tratando de disparar :)\n";
    Position position(mouse_x, mouse_y);
    this->equipment.shoot(position);
}

PlayerImage Player::get_player_image(const Position& position) {
    return PlayerImage(id, Position(position.x, position.y), health, points, money,
                       equipment.get_equiped_code(), std::move(equipment.get_weapons_image()), team,
                       this->mouse_position, this->skins);
}

void Player::buy_weapon(const WeaponCode& weapon_code) {
    equipment.buy_weapon_by_code(weapon_code, money);
}

void Player::drop() { this->equipment.drop_weapon(); }

void Player::change_weapon(const EquipType& equip_type) {
    this->equipment.change_weapon(equip_type);
}
bool Player::equip(std::shared_ptr<IInteractuable>& droppable) {
    return equipment.equip_droppable(droppable);
}
void Player::get_points() {
    this->money += config.earned_points * config.multiplier_points;
    this->points += config.earned_points;
}
void Player::defuse_bomb() { game_zone.defuse_bomb(id); }

void Player::watch(const coordinate_t& mouse_x, const coordinate_t& mouse_y) {
    this->mouse_position.x = mouse_x;
    this->mouse_position.y = mouse_y;
}
