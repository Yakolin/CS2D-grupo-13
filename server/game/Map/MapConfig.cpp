#include "MapConfig.h"

#include <algorithm>
#include <iostream>
Rectangle MapConfig::load_rectangle(const YAML::Node& rectangle) {
    coordinate_t x1 = rectangle["x1"].as<coordinate_t>();
    coordinate_t y1 = rectangle["y1"].as<coordinate_t>();
    coordinate_t x2 = rectangle["x2"].as<coordinate_t>();
    coordinate_t y2 = rectangle["y2"].as<coordinate_t>();
    coordinate_t x_min = std::min(x1, x2);
    coordinate_t y_min = std::min(y1, y2);
    coordinate_t x_max = std::max(x1, x2);
    coordinate_t y_max = std::max(y1, y2);
    Position min(x_min, y_min);
    Position max(x_max, y_max);
    return Rectangle(min, max);
}
void MapConfig::load_bomb_sites(const YAML::Node& bomb_sites) {
    YAML::Node A = bomb_sites["A"];
    YAML::Node B = bomb_sites["B"];
    map_data.bomb_A = load_rectangle(A);
    map_data.bomb_B = load_rectangle(B);
}
void MapConfig::load_spawn_sites(const YAML::Node& spawn_sites) {
    YAML::Node CT = spawn_sites["CT"];
    YAML::Node TT = spawn_sites["TT"];
    map_data.spawn_CT = load_rectangle(CT);
    map_data.spawn_TT = load_rectangle(TT);
}
void MapConfig::load_walls(const YAML::Node& map_walls) {
    for (const auto& wall: map_walls) {
        size_t x1 = wall["x1"].as<size_t>();
        size_t x2 = wall["x2"].as<size_t>();
        size_t y1 = wall["y1"].as<size_t>();
        size_t y2 = wall["y2"].as<size_t>();
        size_t min_x = std::min(x1, x2);
        size_t min_y = std::min(y1, y2);
        size_t max_x = std::max(x1, x2);
        size_t max_y = std::max(y1, y2);
        for (size_t i = min_x; i <= max_x; i++) {
            for (size_t j = min_y; j <= max_y; j++) {
                if (i < map_data.walls.size() && j < map_data.walls[0].size())
                    map_data.walls[i][j] = Wall;
            }
        }
    }
}
void MapConfig::load_map(const YAML::Node& map) {
    YAML::Node bomb_sites = map["bomb_sites"];
    YAML::Node spawn_sites = map["spawn_sites"];
    YAML::Node data = map["map"];
    YAML::Node map_size = data["map_size"];
    YAML::Node walls = data["walls"];
    int width = map_size["x"].as<int>();
    int height = map_size["y"].as<int>();
    this->map_data.walls = std::vector<std::vector<char>>(width, std::vector<char>(height, Floor));
    load_bomb_sites(bomb_sites);
    load_spawn_sites(spawn_sites);
    load_walls(walls);
}
std::string MapConfig::get_map_path(const MapName& map_name) {
    switch (map_name) {
        case MapName::PUEBLITO_AZTECA:
            return PueblitoAzteca_path;
        case MapName::ZONA_ENTRENAMIENTO:
            return ZonaEntrenamiento_path;
        case MapName::DESIERTO:
            return Desierto_path;
        default:
            break;
    }
    throw std::runtime_error("Error in read: this map doesn´t exist");
}
void MapConfig::load(const MapName& map_name) {
    try {
        std::string map_path = get_map_path(map_name);
        YAML::Node map = YAML::LoadFile(map_path);
        load_map(map);
    } catch (const YAML::Exception& e) {
        throw std::runtime_error("Error loading map: " + std::string(e.what()));
    }
}
