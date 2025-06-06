#include "SpecialWeapons.h"

#include <iostream>
void Bomb::set_on_bomb() {
    // Le aviso al timer que tiene que empezar a correr por ser yo la bomba
    timer.bomb_start();
    equiped = false;
    activate = true;
    std::cout << "Bomba activada" << std::endl;
}
void Bomb::set_equiped() { equiped = true; }
void Bomb::set_unequiped() { equiped = false; }
bool Bomb::is_equiped() { return equiped; }
bool Bomb::is_activate() { return activate; }
void Knife::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    ISpawneableZone::collider_solicitude_t wanted = {
            2, 2, direction};  // Es muy cercano, asi que 2 esta bien)?
    spawn.spawn_collider(id, wanted);
}
void Knife::reload() { return; }
WeaponImage Knife::get_weapon_image() {
    return WeaponImage(code, 0, 0, 0);  // Aca evidentemente no maneja balas el cuchillo
}

bool Knife::is_droppable() { return false; }
