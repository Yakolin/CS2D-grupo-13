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

    Skins(CounterTerroristSkin ct_skin, TerroristSkin tt_skin):
            ct_skin(ct_skin), tt_skin(tt_skin) {}
    ~Skins() = default;
};


class GameInfo {
public:
    std::vector<Position> walls;
    GameInfo() {}
    ~GameInfo() {}
};

#endif  // !GAME_INFO_H