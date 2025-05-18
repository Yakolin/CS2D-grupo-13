#ifndef GAME_PHYSICS_H_
#define GAME_PHYSICS_H_
#include <cmath>
#include <utility>
//  "Copyright 2025 Yaco Santamarina"
class Vector2 {
public:
    float x;
    float y;
    Vector2(float _x, float _y): x(_x), y(_y) {}
    Vector2(Vector2&& other) = default;
    Vector2(const Vector2&) = default;
    Vector2 operator+(const Vector2& other) const;
    Vector2& operator+=(const Vector2& other);
    Vector2 operator-(const Vector2& other) const;
    Vector2& operator-=(const Vector2& other);
    Vector2& operator=(Vector2&& other) = default;
    Vector2& operator=(const Vector2& other) = default;
    bool operator==(const Vector2& other) const;
    float get_norm() const;
    Vector2& normalize();
};

class Rectangle {
private:
    Vector2 point_min;
    Vector2 point_max;

public:
    Rectangle(float width, float height, Vector2& point):
            point_min(std::move(point)),
            point_max(std::move(Vector2(point.x + width, point.y + height))) {}
    bool is_in(Vector2& position);
};
#endif  //  GAME_PHYSICS_H_
