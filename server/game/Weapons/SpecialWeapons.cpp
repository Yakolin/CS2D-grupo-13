#include "SpecialWeapons.h"

#include <iostream>
bool Bomb::set_on_action(ISpawneableZone& spawn, player_id_t id,
                         [[maybe_unused]] Position& direction) {
    if (!spawn.plant_bomb(id))
        return false;
    timer.bomb_start();
    state = BombState::ACTIVATED;
    return true;
}

bool Bomb::shoot_burst(ISpawneableZone& spawn, player_id_t id, Position& position) {
    return this->set_on_action(spawn, id, position);
}

void Bomb::defuse() { state = BombState::DESACTIVATED; }
void Bomb::set_equiped() { state = BombState::EQUIPED; }
void Bomb::set_unequiped() { state = BombState::DROPPED; }
void Bomb::set_exploted() { state = BombState::EXPLOTED; }
bool Bomb::is_defused() { return state == BombState::DESACTIVATED; }
bool Bomb::is_equiped() { return state == BombState::EQUIPED; }
bool Bomb::is_activate() { return state == BombState::ACTIVATED; }
WeaponImage Bomb::get_weapon_image() { return WeaponImage(code, 0, 0, 0); }
