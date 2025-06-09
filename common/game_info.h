#ifndef GAME_INFO_H
#define GAME_INFO_H

#include <utility>
#include <vector>

#include "utility.h"

using length_game_info_t = std::uint16_t;
using map_name_t = std::uint8_t;
using skin_t = std::uint8_t;

enum class MapName { DESIERTO, PUEBLITO_AZTECA, ZONA_ENTRENAMIENTO };

enum class TerroristSkin { PHOENIX, L337_KREW, ARCTIC_AVENGER, GUERRILLA };

enum class CounterTerroristSkin { SEAL, GSG9, SAS, GIGN };

class Skins {
public:
    CounterTerroristSkin ct_skin;
    TerroristSkin tt_skin;

    Skins(const CounterTerroristSkin& ct_skin, const TerroristSkin& tt_skin):
            ct_skin(ct_skin), tt_skin(tt_skin) {}
    ~Skins() = default;
};
class WeaponInfo {
public:
    WeaponInfo(WeaponCode code, uint16_t price): code(code), price(price) {}
    ~WeaponInfo() {}
    WeaponCode code;
    uint16_t price;
};
class RectangleInfo {
public:
    RectangleInfo() = default;
    Position pos_min;
    Position pos_max;
    RectangleInfo(const Position& pos_min, const Position& pos_max):
            pos_min(pos_min), pos_max(pos_max) {}
};

class MapInfo {
public:
    RectangleInfo bomb_A, bomb_B, spawn_TT, spawn_CT;
    std::vector<Position> walls;
    MapInfo() = default;
    MapInfo(const RectangleInfo& bomb_A, const RectangleInfo& bomb_B, const RectangleInfo& spawn_TT,
            const RectangleInfo& spawn_CT, const std::vector<Position>& walls):
            bomb_A(bomb_A), bomb_B(bomb_B), spawn_TT(spawn_TT), spawn_CT(spawn_CT), walls(walls) {}
    ~MapInfo() {}
};

class GameInfo {
public:
    GameInfo() {}
    GameInfo(const MapInfo& map_info, const std::vector<WeaponInfo>& weapons_purchasables):
            map_info(map_info), weapons_purchasables(weapons_purchasables) {}
    ~GameInfo() {}
    MapInfo map_info;
    std::vector<WeaponInfo> weapons_purchasables;
};
#endif  // !GAME_INFO_H
