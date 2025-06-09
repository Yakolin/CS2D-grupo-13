#include "WeaponFactory.h"

Weapon::weapon_specs_t WeaponFactory::find_weapon_specs(WeaponCode code) {
    auto it = weapon_configs.find(code);
    if (it == weapon_configs.end())
        throw std::runtime_error("Error while reading a weapon config");
    GameConfig::WeaponConfig& config = it->second;
    Weapon::weapon_specs_t specs = {config.price, config.damage,    config.fire_rate,
                                    config.max_b, config.current_b, config.current_b,
                                    config.width, config.distance};
    return specs;
}
std::shared_ptr<Weapon> WeaponFactory::weapon_create(WeaponCode code) {
    if (code == WeaponCode::NONE)
        return std::make_unique<NullWeapon>();
    Weapon::weapon_specs_t config = find_weapon_specs(code);
    switch (code) {
        case WeaponCode::GLOCK:
            return std::make_unique<Glock>(config);
            break;
        case WeaponCode::AK47:
            return std::make_unique<Ak47>(config);
            break;
        case WeaponCode::KNIFE:
            return std::make_unique<Knife>(config);
            break;
        default:
            break;
    }
    return nullptr;
}
uint16_t WeaponFactory::price_weapon(WeaponCode code) {
    Weapon::weapon_specs_t config = find_weapon_specs(code);
    return config.price;
}
