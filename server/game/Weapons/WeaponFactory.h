#ifndef WEAPON_FACTORY_H_
#define WEAPON_FACTORY_H_
#include <map>
#include <memory>

#include "../Config/GameConfig.h"
#include "../Weapons/FireableWeapon.h"
#include "../Weapons/SpecialWeapons.h"
#include "../Weapons/Weapon.h"
class WeaponFactory {
private:
    std::map<WeaponCode, GameConfig::WeaponConfig>& weapon_configs;
    GameConfig::weapon_config_t find_weapon_specs(WeaponCode code);

public:
    explicit WeaponFactory(std::map<WeaponCode, GameConfig::WeaponConfig>& weapon_configs):
            weapon_configs(weapon_configs) {}
    std::shared_ptr<Weapon> weapon_create(WeaponCode code);
    uint16_t price_weapon(WeaponCode code);
};
#endif  // WEAPON_FACTORY_H_
