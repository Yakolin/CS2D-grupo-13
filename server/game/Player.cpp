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
        equipment.primary = nullptr;
        equipment.secondary = nullptr;
        equipment.secondary = std::make_unique<Glock>();
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
    equipment.secondary->reload();
}
void Player::shoot(const coordinate_t& mouse_x, const coordinate_t& mouse_y) {
    Position direction(mouse_x, mouse_y);
    equipment.secondary->set_on_action(spawneable_zone, id, direction);
}

PlayerImage Player::get_player_image(const Position& position, Team team) {
    return PlayerImage(id, Position(position.x, position.y), health, points,
                       std::move(equipment.get_weapons_image()));
}

void Player::drop() { this->equipment.drop_weapon(this->id, this->droppable_zone); }
