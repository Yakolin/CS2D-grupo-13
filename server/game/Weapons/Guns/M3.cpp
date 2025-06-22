#include "M3.h"

M3::M3(GameConfig::weapon_config_t specs):
        FireableWeapon(WeaponCode::M3, specs.damage, specs.distance, specs.width, specs.chance_hit,
                       std::make_unique<SemiAutomatic>(static_cast<timer_fire_t>(specs.timer_fire)),
                       specs.max_b, specs.current_b) {}

M3::~M3() {}


damage_t M3::calculate_damage(float distance) { return (std::round(Weapon::damage / distance)); }

bool M3::is_droppable() { return true; }
