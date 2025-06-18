#include "knife.h"


Knife::Knife(): Weapon(Weapon) {}

Knife::~Knife() {}

bool Knife::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    auto function_damage = [this]([[maybe_unused]] float distance) { return specs.damage; };
    ISpawneableZone::collider_solicitude_t wanted = {specs.width, specs.distance, direction,
                                                     function_damage};

    spawn.spawn_collider(id, wanted);
    return true;
}

void Knife::reload() {}

WeaponImage Knife::get_weapon_image() { return WeaponImage(code, 0, 0, 0); }

bool Knife::is_droppable() { return false; }

void Knife::reset() {}
