#include "Awp.h"

Awp::Awp(GameConfig::weapon_config_t specs):
        FireableWeapon(WeaponCode::AWP, specs.damage, specs.distance, specs.width, specs.chance_hit,
                       std::make_unique<SemiAutomatic>(static_cast<timer_fire_t>(specs.timer_fire)),
                       specs.max_b, specs.current_b) {}

Awp::~Awp() {}

bool Awp::is_droppable() { return true; }

damage_t Awp::calculate_damage([[maybe_unused]] float distance) { return Weapon::damage; }
