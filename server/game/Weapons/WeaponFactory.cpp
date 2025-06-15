#include "WeaponFactory.h"

GameConfig::weapon_config_t WeaponFactory::find_weapon_specs(WeaponCode code) {
    auto it = weapon_configs.find(code);
    if (it == weapon_configs.end())
        throw std::runtime_error("Error while reading a weapon config");
    GameConfig::WeaponConfig& config = it->second;
    return config;
}
std::shared_ptr<Weapon> WeaponFactory::create_random_weapon() {
    int rand_value = rand() % 3;  // Muy mejorable esta funcion...
    if (rand_value == 0)
        return weapon_create(WeaponCode::AK47);
    else if (rand_value == 1)
        return weapon_create(WeaponCode::M3);
    else if (rand_value == 2)
        return weapon_create(WeaponCode::AWP);
    else
        return weapon_create(WeaponCode::NONE);  // Esto casi que es una exception...
}
std::shared_ptr<Weapon> WeaponFactory::weapon_create(WeaponCode code) {
    if (code == WeaponCode::NONE)
        return std::make_unique<NullWeapon>();
    GameConfig::weapon_config_t config = find_weapon_specs(code);
    switch (code) {
        case WeaponCode::GLOCK:
            return std::make_unique<Glock>(config);
        case WeaponCode::AK47:
            return std::make_unique<Ak47>(config);
        case WeaponCode::M3:
            return std::make_unique<M3>(config);
        case WeaponCode::AWP:
            return std::make_unique<AWP>(config);
        case WeaponCode::KNIFE:
            return std::make_unique<Knife>(config);
        default:
            break;
    }
    return nullptr;
}
uint16_t WeaponFactory::price_weapon(WeaponCode code) {
    GameConfig::weapon_config_t config = find_weapon_specs(code);
    return config.price;
}
