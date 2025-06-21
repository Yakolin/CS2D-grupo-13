#include "Glock.h"

Glock::Glock(GameConfig::weapon_config_t specs):
        FireableWeapon(WeaponCode::GLOCK, specs.damage, specs.distance, specs.width,
                       std::make_unique<SemiAutomatic>(static_cast<fire_rate_t>(specs.fire_rate)),
                       specs.max_b, specs.current_b) {}

Glock::~Glock() {}


bool Glock::is_droppable() { return false; }

damage_t Glock::calculate_damage(float distance) { return (Weapon::damage * distance); }
