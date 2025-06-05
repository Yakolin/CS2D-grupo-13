#include "SpecialWeapons.h"

void set_on_bomb() {
    // Le aviso al timer que tiene que empezar a correr por ser yo la bomba
}
WeaponImage Bomb::get_weapon_image() { return WeaponImage(WeaponCode::BOMB, 0, 0, 0); }

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
