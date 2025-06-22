#include "Player.h"

#include <memory>
void Player::damage(uint8_t damage) {
    if (damage > health)
        health = 0;
    else
        health -= damage;
    sound_zone.want_emit_sound(id, std::make_shared<Sound>(SoundType::HIT));
    if (is_dead()) {
        this->deaths++;
        equipment.drop_all();
        sound_zone.want_emit_sound(id, std::make_shared<Sound>(SoundType::DIE));
    }
}
bool Player::is_dead() { return health == 0; }

void Player::reset(bool full_reset) {
    if (full_reset || health == 0) {
        equipment.reset_equipment();
    } else {
        equipment.restore();
    }
    health = config.health;
}
void Player::move(const MoveType& move_type) {
    Position pos(0, 0);
    switch (move_type) {
        case MoveType::RIGHT:
            pos = Position(1, 0);
            break;
        case MoveType::LEFT:
            pos = Position(-1, 0);
            break;
        case MoveType::UP:
            pos = Position(0, 1);
            break;
        case MoveType::DOWN:
            pos = Position(0, -1);
            break;
    }
    if (game_zone.move(id, pos)) {
        sound_zone.want_emit_sound(id, std::make_shared<Sound>(SoundType::WALK));
    }
}

void Player::reload() { this->equipment.reload(); }

void Player::shoot(const coordinate_t& mouse_x, const coordinate_t& mouse_y) {
    Position position(mouse_x, mouse_y);
    this->equipment.shoot(position);
}

void Player::shoot_burst(const coordinate_t& mouse_x, const coordinate_t& mouse_y) {
    Position position(mouse_x, mouse_y);
    this->equipment.shoot_burst(position);
}

PlayerImage Player::get_player_image(const Position& position, SoundImage& sounds) {
    return PlayerImage(id, Position(position.x, position.y), health, deaths, points, money,
                       equipment.get_equiped_code(), std::move(equipment.get_weapons_image()), team,
                       this->mouse_position, this->skins, std::move(sounds));
}

void Player::buy_weapon(const WeaponCode& weapon_code) {
    equipment.buy_weapon_by_code(weapon_code, this->money);
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
    this->collected_money += config.earned_points * config.multiplier_points;
    this->points += config.earned_points;
    // Sonido de ganar puntos...
}
void Player::defuse_bomb() { game_zone.defuse_bomb(id); }

void Player::watch(const coordinate_t& mouse_x, const coordinate_t& mouse_y) {
    this->mouse_position.x = mouse_x;
    this->mouse_position.y = mouse_y;
}
