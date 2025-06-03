#include "SpecialWeapons.h"

void Knife::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    ISpawneableZone::damage_collider_t wanted = {
            2, 2, direction};  // Es muy cercano, asi que 2 esta bien)?
    spawn.spawn_collider(id, wanted);
}
void Knife::reload() { return; }
WeaponImage Knife::get_weapon_image() {
    return WeaponImage(code, 0, 0, 0);  // Aca evidentemente no maneja balas el cuchillo
}
