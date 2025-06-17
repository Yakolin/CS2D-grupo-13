#include "awp.h"

Awp::Awp(GameConfig::weapon_config_t specs): FireableWeapon(WeaponCode::AWP, specs) {}

Awp::~Awp() {}

bool Awp::is_droppable() { return true; }

uint8_t Awp::calculate_damage([[maybe_unused]] float distance) { return specs.damage; }

bool FireableWeapon::reduce_bullets() {
    if (specs.current_b == 0)
        return false;
    uint8_t bullets_fired = std::min(specs.current_b, specs.fire_rate);
    specs.current_b -= bullets_fired;
    return true;
}

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