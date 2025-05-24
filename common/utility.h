#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>

#include "player_command_types.h"

class Position {
public:
    coordinate_t x;
    coordinate_t y;

    Position(coordinate_t x, coordinate_t y): x(x), y(y) {}
    Position(const Position&) = default;
    ~Position() = default;

    Position& operator=(const Position& other) = default;
    Position& operator=(Position&& other) = default;

    bool operator==(const Position& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Position& other) const { return !(*this == other); }

    Position operator+(const Position& other) const {
        return Position(this->x + other.x, this->y + other.y);
    }

    Position& operator+=(const Position& other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Position operator-(const Position& other) const {
        return Position(this->x - other.x, this->y - other.y);
    }

    Position& operator-=(const Position& other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    coordinate_t get_norm() const { return std::sqrt(x * x + y * y); }
};

#endif  // !UTILITY_H