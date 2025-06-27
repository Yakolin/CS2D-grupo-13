#include "WeaponFactory.h"

GameConfig::weapon_config_t WeaponFactory::find_weapon_specs(WeaponCode code) {
    auto it = weapon_configs.find(code);
    if (it == weapon_configs.end())
        throw std::runtime_error("Error while reading a weapon config");
    GameConfig::WeaponConfig& config = it->second;
    return config;
}
std::shared_ptr<FireableWeapon> WeaponFactory::create_random_weapon(
        const GameConfig::dropped_weapons_t& dropped_weapons) {
    std::random_device rd;
    std::mt19937 rand(rd());
    int total =
            dropped_weapons.awp_chance + dropped_weapons.ak47_chance + dropped_weapons.m3_chance;
    std::uniform_int_distribution<> dis(0, total);
    int rand_value = dis(rand);
    if (rand_value < dropped_weapons.awp_chance)
        return weapon_create(WeaponCode::AWP);
    else if (rand_value < dropped_weapons.ak47_chance)
        return weapon_create(WeaponCode::AK47);
    else
        return weapon_create(WeaponCode::M3);
}

std::shared_ptr<Weapon> WeaponFactory::create_knife() {
    GameConfig::weapon_config_t config = find_weapon_specs(WeaponCode::KNIFE);
    return std::make_shared<Knife>(config);
}

std::shared_ptr<FireableWeapon> WeaponFactory::weapon_create(WeaponCode code) {
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
            return std::make_unique<Awp>(config);
        default:
            break;
    }
    return nullptr;
}
uint16_t WeaponFactory::price_weapon(WeaponCode code) {
    GameConfig::weapon_config_t config = find_weapon_specs(code);
    return config.price;
}
