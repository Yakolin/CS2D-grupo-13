#ifndef GAME_INFO_H
#define GAME_INFO_H

#include <utility>
#include <vector>

#include "utility.h"

using length_game_info_t = std::uint16_t;

class GameInfo {
public:
    std::vector<Position> walls;
    GameInfo() {}
    ~GameInfo() {}
};

#endif  // !GAME_INFO_H