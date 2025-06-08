#include "MapConfig.h"

MapConfig::MapConfig(const MapName& map_name) { load(map_name); }

/*
void MapConfig::load_player(const YAML::Node& config) {
    YAML::Node player = config["Player"];
    player_config = {player["health"].as<uint8_t>(), player["money"].as<uint16_t>(),
                     player["points"].as<uint16_t>(), player["earned_points"].as<uint16_t>(),
                     player["multiplier_points"].as<uint8_t>()};
}
*/

void load_map(const YAML::Node& map) { YAML::Node test = map["prueba"]; }
std::string MapConfig::get_map_path(const MapName& map_name) {
    switch (map_name) {
        case MapName::PUEBLITO_AZTECA:
            return PueblitoAzteca_path;
        default:
            break;
    }
}
void MapConfig::load(const MapName& map_name) {
    try {
        std::string map_path = get_map_path(map_name);
        YAML::Node map = YAML::LoadFile(map_path);
        load_map(map);
    } catch (const YAML::Exception& e) {
        throw std::runtime_error("Error al leer archivo YAML en Map: " + std::string(e.what()));
    }
}
