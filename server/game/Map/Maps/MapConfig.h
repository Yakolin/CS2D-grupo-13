#ifndef GAME_CONFIG_H_
#define GAME_CONFIG_H_
#include <fstream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <yaml-cpp/yaml.h>

#include "../../../../common/game_info.h"
#include "../../Colliders/Colliders.h"

#define PueblitoAzteca_path "server/game/Map/MapConfig/Azteca.yaml"

class MapConfig {
public:
    typedef struct MapInfo {
        Rectangle bomb_A, bomb_B, spawn_CT, spawn_TT;
        std::vector<Position> walls;
    } map_info_t;

private:
    std::string get_map_path(const MapName& map_name);
    void load(const MapName& map_name);

public:
    explicit MapConfig(const MapName& map_name);
};

#endif  // GAME_CONFIG_H_
