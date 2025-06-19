#include "Awp.h"

Awp::Awp(GameConfig::weapon_config_t specs):
        FireableWeapon(WeaponCode::AWP, specs.damage, specs.distance, specs.width,
                       std::make_unique<SemiAutomatic>(static_cast<fire_rate_t>(specs.fire_rate)),
                       specs.max_b, specs.current_b) {}

Awp::~Awp() {}

bool Awp::is_droppable() { return true; }

damage_t Awp::calculate_damage() { return Weapon::damage; }
