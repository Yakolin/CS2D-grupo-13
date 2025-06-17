#include "Glock.h"

Glock::Glock(GameConfig::weapon_config_t specs): FireableWeapon(WeaponCode::GLOCK, specs) {}

Glock::~Glock() {}

bool Glock::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (!have_bullets()) {
        reduce_bullets();
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

uint8_t Glock::calculate_damage(float distance) { return specs.damage * distance; }
