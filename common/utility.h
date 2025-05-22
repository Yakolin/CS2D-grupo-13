#ifndef UTILITY_H
#define UTILITY_H

#include <cstdint>

using coordinate_t = std::uint16_t;

<<<<<<< HEAD
class Position {  // Esto puede ser directamente un Vector2
=======
class Position {
>>>>>>> main
public:
    coordinate_t x;
    coordinate_t y;

    Position(coordinate_t x, coordinate_t y): x(x), y(y) {}
    ~Position() = default;
<<<<<<< HEAD
=======

>>>>>>> main
    bool operator==(const Position& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Position& other) const { return !(*this == other); }
};

<<<<<<< HEAD

#endif  // UTILITY_H
=======
#endif  // UTILITY_H
>>>>>>> main
