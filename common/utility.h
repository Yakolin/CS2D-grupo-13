#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>

#include "player_command_types.h"

class Position {
public:
    coordinate_t x;
    coordinate_t y;
    Position(): x(0), y(0) {}
    Position(coordinate_t _x, coordinate_t _y): x(_x), y(_y) {}
    Position(Position&& other) = default;
    Position(const Position&) = default;
    Position operator+(const Position& other) const;
    Position& operator+=(const Position& other);
    Position operator-(const Position& other) const;
    Position& operator-=(const Position& other);
    Position& operator=(Position&& other) = default;
    Position& operator=(const Position& other) = default;
    bool operator==(const Position& other) const;
    coordinate_t get_norm() const;  // Falta implementar
    Position& normalize();
    float distance(const Position& other) const;
};


#endif  // !UTILITY_H
