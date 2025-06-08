#include "SpecialWeapons.h"

#include <iostream>
bool Bomb::set_on_action(ISpawneableZone& spawn, player_id_t id,
                         [[maybe_unused]] Position& direction) {
    if (!spawn.plant_bomb(id))
        return false;
    timer.bomb_start();
    equiped = false;
    activate = true;
    return true;
}
void Bomb::defuse() { defused = true; }
void Bomb::set_equiped() { equiped = true; }
void Bomb::set_unequiped() { equiped = false; }
bool Bomb::is_defused() { return defused; }
bool Bomb::is_equiped() { return equiped; }
bool Bomb::is_activate() { return activate; }
WeaponImage Bomb::get_weapon_image() { return WeaponImage(code, 0, 0, 0); }
