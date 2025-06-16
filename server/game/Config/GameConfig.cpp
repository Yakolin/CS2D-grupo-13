#include "GameConfig.h"

// Quiza el hardcodeo este este mal)?
GameConfig::GameConfig() { load("Config/GameConfig.yaml"); }

WeaponCode GameConfig::weapon_name_to_code(const std::string& name) {
    if (name == "Glock")
        return WeaponCode::GLOCK;
    else if (name == "Ak47")
        return WeaponCode::AK47;
    else if (name == "M3")
        return WeaponCode::M3;
    else if (name == "AWP")
        return WeaponCode::AWP;
    else if (name == "Knife")
        return WeaponCode::KNIFE;
    else
        throw std::invalid_argument("Named weapon doesn´t exist " + name);
}
void GameConfig::load_weapons(const YAML::Node& config) {
    YAML::Node weapons = config["Weapons"];
    for (const auto& weapon: weapons) {
        std::string name = weapon.first.as<std::string>();
        WeaponCode code = weapon_name_to_code(name);
        YAML::Node data = weapon.second;
        bool purchasable = data["purchasable"].as<bool>();
        WeaponConfig weapon_config{
                data["price"].as<price_t>(),          data["damage"].as<damage_t>(),
                data["fire_rate"].as<fire_rate_t>(),  data["max_bullets"].as<max_bullets_t>(),
                data["magazine"].as<max_bullets_t>(), data["width"].as<width_t>(),
                data["distance"].as<distance_t>(),    purchasable};
        weapon_configs[code] = weapon_config;
    }
}
void GameConfig::load_timers(const YAML::Node& config) {
    YAML::Node timer = config["Timer"];
    timer_config = {timer["time_buy"].as<int>(), timer["time_round"].as<int>(),
                    timer["time_bomb"].as<int>(), timer["time_ending"].as<int>()};
}
void GameConfig::load_player(const YAML::Node& config) {
    YAML::Node player = config["Player"];
    player_config = {player["health"].as<health_t>(), player["money"].as<money_t>(),
                     player["points"].as<points_t>(), player["earned_points"].as<earned_points_t>(),
                     player["multiplier_points"].as<multiplier_points_t>()};
}
void GameConfig::load_general_configs(const YAML::Node& config) {
    dropped_weapons = config["RandomWeapons"].as<uint8_t>();
}
void GameConfig::load(const std::string& file_path) {
    try {
        YAML::Node config = YAML::LoadFile(file_path);
        load_weapons(config);
        load_timers(config);
        load_player(config);
        load_general_configs(config);
    } catch (const YAML::Exception& e) {
        throw std::runtime_error("Error al leer archivo YAML: " + std::string(e.what()));
    }
}
std::vector<WeaponInfo> GameConfig::get_info_weapons() {
    std::vector<WeaponInfo> aux;
    for (const auto& weapon: weapon_configs) {
        if (weapon.second.purchasable) {
            WeaponInfo info(weapon.first, weapon.second.price);
            aux.push_back(info);
        }
    }
    return aux;
}
