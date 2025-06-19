#include "M3.h"

M3::M3(GameConfig::weapon_config_t specs):
        FireableWeapon(WeaponCode::M3, specs.damage, specs.distance, specs.width,
                       std::make_unique<SemiAutomatic>(static_cast<fire_rate_t>(specs.fire_rate)),
                       specs.max_b, specs.current_b) {}

M3::~M3() {}


damage_t M3::calculate_damage() { return (std::round(Weapon::damage / Weapon::range)); }

bool M3::is_droppable() { return true; }
