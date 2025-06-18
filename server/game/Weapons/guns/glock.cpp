#include "glock.h"

Glock::Glock():
        Weapon(WeaponConfig::get_instance()["weapon"]["glock"]["damage"].as<damage_t>,
               std::make_unique<SemiAutomatic>()),
        FireableWeapon(
                WeaponConfig::get_instance()["weapon"]["glock"]["max_bullets"].as<bullet_t>,
                WeaponConfig::get_instance()["weapon"]["glock"]["magazine"].as<magazine_t>,
                WeaponConfig::get_instance()["weapon"]["glock"]["fire_rate"].as<fire_rate_t>) {}

Glock::~Glock() {}

bool Glock::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
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
bool Glock::is_droppable() { return false; }

damage_t Glock::calculate_damage(float distance) { return this->damage * distance; }

void Glock::reset(FireableWeapon::restore_bullets();)
