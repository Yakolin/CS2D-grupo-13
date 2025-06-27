#include "Glock.h"

Glock::Glock(GameConfig::weapon_config_t specs):
        FireableWeapon(WeaponCode::GLOCK, specs.damage, specs.distance, specs.width,
                       specs.chance_hit,
                       std::make_unique<SemiAutomatic>(static_cast<timer_fire_t>(specs.timer_fire)),
                       specs.max_b, specs.current_b) {}

Glock::~Glock() {}


bool Glock::is_droppable() { return false; }

damage_t Glock::calculate_damage(float distance) { return (Weapon::damage * distance); }
