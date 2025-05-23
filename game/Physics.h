#ifndef GAME_PHYSICS_H_
#define GAME_PHYSICS_H_
#include <cmath>
#include <utility>

#include "../common/player_command_types.h"
//  "Copyright 2025 Yaco Santamarina"
class Vector2 {
public:
    coordinate_t x;
    coordinate_t y;
    Vector2(coordinate_t _x, coordinate_t _y): x(_x), y(_y) {}
    Vector2(Vector2&& other) = default;
    Vector2(const Vector2&) = default;
    Vector2 operator+(const Vector2& other) const;
    Vector2& operator+=(const Vector2& other);
    Vector2 operator-(const Vector2& other) const;
    Vector2& operator-=(const Vector2& other);
    Vector2& operator=(Vector2&& other) = default;
    Vector2& operator=(const Vector2& other) = default;
    bool operator==(const Vector2& other) const;
    coordinate_t get_norm() const;  // Falta implementar
    Vector2& normalize();
    float distance(const Vector2& other);
};
#endif  //  GAME_PHYSICS_H_
