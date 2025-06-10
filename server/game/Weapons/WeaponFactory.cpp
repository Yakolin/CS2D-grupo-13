#include "WeaponFactory.h"

GameConfig::weapon_config_t WeaponFactory::find_weapon_specs(WeaponCode code) {
    auto it = weapon_configs.find(code);
    if (it == weapon_configs.end())
        throw std::runtime_error("Error while reading a weapon config");
    GameConfig::WeaponConfig& config = it->second;
    return config;
}
std::shared_ptr<Weapon> WeaponFactory::weapon_create(WeaponCode code) {
    if (code == WeaponCode::NONE)
        return std::make_unique<NullWeapon>();
    GameConfig::weapon_config_t config = find_weapon_specs(code);
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
    GameConfig::weapon_config_t config = find_weapon_specs(code);
    return config.price;
}
