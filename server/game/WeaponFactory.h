#ifndef WEAPON_FACTORY_H_
#define WEAPON_FACTORY_H_
#include <map>
#include <memory>

#include "FireableWeapon.h"
#include "GameConfig.h"
#include "SpecialWeapons.h"
#include "Weapon.h"
class WeaponFactory {
private:
    std::map<WeaponCode, GameConfig::WeaponConfig>& weapon_configs;
    Weapon::weapon_specs_t find_weapon_specs(WeaponCode code);

public:
    explicit WeaponFactory(std::map<WeaponCode, GameConfig::WeaponConfig>& weapon_configs):
            weapon_configs(weapon_configs) {}
    std::shared_ptr<Weapon> weapon_create(WeaponCode code);
    uint16_t price_weapon(WeaponCode code);
};
#endif  // WEAPON_FACTORY_H_
