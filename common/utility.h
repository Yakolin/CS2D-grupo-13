#ifndef UTILITY_H
#define UTILITY_H

#include <cstdint>

using coordinate_t = std::uint16_t;

class Position {
public:
    coordinate_t x;
    coordinate_t y;

    Position(coordinate_t x, coordinate_t y): x(x), y(y) {}
    ~Position() = default;

    bool operator==(const Position& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Position& other) const { return !(*this == other); }
};

#endif  // UTILITY_H