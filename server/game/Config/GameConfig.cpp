#include "GameConfig.h"

// Quiza el hardcodeo este este mal)?
GameConfig::GameConfig() { load("server/game/Config/GameConfig.yaml"); }

WeaponCode GameConfig::weapon_name_to_code(const std::string& name) {
    if (name == "Glock")
        return WeaponCode::GLOCK;
    else if (name == "Ak47")
        return WeaponCode::AK47;
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
        WeaponConfig weapon_config{
                data["price"].as<uint16_t>(),    data["damage"].as<uint8_t>(),
                data["fire_rate"].as<uint8_t>(), data["max_bullets"].as<uint8_t>(),
                data["magazine"].as<uint8_t>(),  data["width"].as<uint8_t>(),
                data["distance"].as<uint8_t>(),
        };
        weapon_configs[code] = weapon_config;
    }
}
void GameConfig::load_timers(const YAML::Node& config) {
    YAML::Node timer = config["Timer"];
    timer_config = {timer["time_buy"].as<int>(), timer["time_round"].as<int>(),
                    timer["time_after_round"].as<int>(), timer["time_bomb"].as<int>()};
}
void GameConfig::load_player(const YAML::Node& config) {
    YAML::Node player = config["Player"];
    player_config = {player["health"].as<uint8_t>(), player["money"].as<uint16_t>(),
                     player["points"].as<uint16_t>(), player["earned_points"].as<uint16_t>(),
                     player["multiplier_points"].as<uint8_t>()};
}
void GameConfig::load(const std::string& file_path) {
    try {
        YAML::Node config = YAML::LoadFile(file_path);
        load_weapons(config);
        load_timers(config);
        load_player(config);
    } catch (const YAML::Exception& e) {
        throw std::runtime_error("Error al leer archivo YAML: " + std::string(e.what()));
    }
}
