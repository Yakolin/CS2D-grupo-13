#include "Ak47.h"


Ak47::Ak47(GameConfig::weapon_config_t specs):
        FireableWeapon(
                WeaponCode::AK47, specs.damage, specs.distance, specs.width,
                std::make_unique<Automatic>(specs.fire_rate, specs.timer_fire, specs.burst_coldown),
                specs.max_b, specs.current_b) {}


damage_t Ak47::calculate_damage(float distance) { return (Weapon::damage * distance); }

Ak47::~Ak47() {}

bool Ak47::is_droppable() { return true; }
