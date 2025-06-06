#include "GameConfig.h"

// Quiza el hardcodeo este este mal)?
GameConfig::GameConfig() { load("GameConfig.yaml"); }

void GameConfig::load_timers(const YAML::Node& config) {
    YAML::Node timer = config["Timer"];
    timer_config = {timer["time_buy"].as<int>(), timer["time_round"].as<int>(),
                    timer["time_after_round"].as<int>(), timer["time_bomb"].as<int>()};
}
void GameConfig::load(const std::string& file_path) {
    try {
        YAML::Node config = YAML::LoadFile(file_path);
        // load_weapons(config);
        load_timers(config);
    } catch (const YAML::Exception& e) {
        throw std::runtime_error("Error al leer archivo YAML: " + std::string(e.what()));
    }
}
