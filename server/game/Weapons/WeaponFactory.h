#ifndef WEAPON_FACTORY_H_
#define WEAPON_FACTORY_H_
#include <map>
#include <memory>
#include <random>

#include "../Config/GameConfig.h"
#include "Guns/Ak47.h"
#include "Guns/Awp.h"
#include "Guns/Glock.h"
#include "Guns/Knife.h"
#include "Guns/M3.h"
#include "Guns/NullWeapon.h"

#include "FireableWeapon.h"
#include "SpecialWeapons.h"
#include "Weapon.h"

class WeaponFactory {
private:
    std::map<WeaponCode, GameConfig::WeaponConfig>& weapon_configs;
    GameConfig::weapon_config_t find_weapon_specs(WeaponCode code);

public:
    explicit WeaponFactory(std::map<WeaponCode, GameConfig::WeaponConfig>& weapon_configs):
            weapon_configs(weapon_configs) {}

    std::shared_ptr<FireableWeapon> create_random_weapon(
            const GameConfig::dropped_weapons_t& dropped_weapons);
    std::shared_ptr<Weapon> create_knife();
    std::shared_ptr<FireableWeapon> weapon_create(WeaponCode code);
    uint16_t price_weapon(WeaponCode code);
};
#endif  // WEAPON_FACTORY_H_
