#ifndef GAME_INFO_H
#define GAME_INFO_H

#include <utility>
#include <vector>

#include "utility.h"

class GameInfo {
public:
    std::vector<Position> walls;
    GameInfo(std::vector<Position>&& walls): walls(std::move(walls)) {}
    ~GameInfo() {}
};

#endif  // !GAME_INFO_H