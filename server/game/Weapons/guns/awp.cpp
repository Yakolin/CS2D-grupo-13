#include "awp.h"

Awp::Awp():
        Weapon(WeaponConfig::get_instance()["weapon"]["awp"]["damage"].as<damage_t>,
               std::make_unique<SemiAutomatic>()),
        FireableWeapon(WeaponConfig::get_instance()["weapon"]["awp"]["max_bullets"].as<bullet_t>,
                       WeaponConfig::get_instance()["weapon"]["awp"]["magazine"].as<magazine_t>,
                       WeaponConfig::get_instance()["weapon"]["awp"]["fire_rate"].as<fire_rate_t>) {
}

Awp::~Awp() {}

bool Awp::is_droppable() { return true; }

damage_t Awp::calculate_damage([[maybe_unused]] float distance) { return this->damage; }

bool Awp::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
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

void Awp::reset(FireableWeapon::restore_bullets();)