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

#define Wall '#'
#define Floor ' '

#define PueblitoAzteca_path "server/game/Map/Maps/Azteca.yaml"

class MapConfig {
public:
    typedef struct MapInfo {
        Rectangle bomb_A, bomb_B, spawn_CT, spawn_TT;
        std::vector<std::vector<char>> walls;
    } map_info_t;
    map_info_t map_info;

private:
    Rectangle load_rectangle(const YAML::Node& rectangle);
    void load_bomb_sites(const YAML::Node& bomb_sites);
    void load_spawn_sites(const YAML::Node& spawn_sites);
    void load_walls(const YAML::Node& map_walls);
    void load_map(const YAML::Node& map);
    std::string get_map_path(const MapName& map_name);
    void load(const MapName& map_name);

public:
    explicit MapConfig(const MapName& map_name) { load(map_name); }
    map_info_t& get_map_info() { return map_info; }
};

#endif  // MAP_CONFIG_H_
