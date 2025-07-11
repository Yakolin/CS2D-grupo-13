#ifndef MAP_CONFIG_H_
#define MAP_CONFIG_H_
#include <fstream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <yaml-cpp/yaml.h>

#include "../../../common/game_info.h"
#include "../Colliders/Colliders.h"

#define PueblitoAzteca_path "server/game/Map/Maps/Azteca.yaml"
#define ZonaEntrenamiento_path "server/game/Map/Maps/Entrenamiento.yaml"
#define Desierto_path "server/game/Map/Maps/Desierto.yaml"

class MapConfig {
public:
    typedef struct MapData {
        Rectangle bomb_A, bomb_B, spawn_CT, spawn_TT;
        size_t width;
        size_t height;
        std::vector<Position> boxes_pos;
        std::vector<Position> walls_pos;
    } map_data_t;
    map_data_t map_data;

private:
    Rectangle load_rectangle(const YAML::Node& rectangle);
    void load_bomb_sites(const YAML::Node& bomb_sites);
    void load_spawn_sites(const YAML::Node& spawn_sites);
    void load_walls(const YAML::Node& map_walls);
    void load_boxes(const YAML::Node& map_boxes);
    void load_map(const YAML::Node& map);
    std::string get_map_path(const MapName& map_name);
    void load(const MapName& map_name);

public:
    explicit MapConfig(const MapName& map_name) { load(map_name); }
    map_data_t& get_map_data() { return map_data; }
};

#endif  // MAP_CONFIG_H_
