#include "awp.h"

Awp::Awp(GameConfig::weapon_config_t specs): FireableWeapon(WeaponCode::AWP, specs) {}

Awp::~Awp() {}

bool AWP::is_droppable() { return true; }

uint8_t AWP::calculate_damage([[maybe_unused]] float distance) { return specs.damage; }
bool FireableWeapon::reduce_bullets() {
    if (specs.current_b == 0)
        return false;
    uint8_t bullets_fired = std::min(specs.current_b, specs.fire_rate);
    specs.current_b -= bullets_fired;
    return true;
}