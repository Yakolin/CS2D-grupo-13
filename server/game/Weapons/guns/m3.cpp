#include "m3.h"

M3::M3():
        Weapon(WeaponConfig::get_instance()["weapon"]["glock"]["damage"].as<damage_t>,
               std::make_unique<SemiAutomatic>()),
        FireableWeapon(
                WeaponConfig::get_instance()["weapon"]["glock"]["max_bullets"].as<bullet_t>,
                WeaponConfig::get_instance()["weapon"]["glock"]["magazine"].as<magazine_t>,
                WeaponConfig::get_instance()["weapon"]["glock"]["fire_rate"].as<fire_rate_t>) {}

M3::~M3() {}

bool M3::is_droppable() { return true; }

damage_t M3::calculate_damage(float distance) { return (this->damage / distance); }

bool M3::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (reduce_bullets()) {
        auto calculate_damage_func = [this](float distance) {
            return this->calculate_damage(distance);
        };
        ISpawneableZone::collider_solicitude_t wanted = {specs.width, specs.distance, direction,
                                                         calculate_damage_func};
        spawn.spawn_collider(id, wanted);
    }
    return true;
}

void M3::reload() { FireableWeapon::reload(); }

void M3::reset() { FireableWeapon::restore_bullets(); }