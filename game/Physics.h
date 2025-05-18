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
    float width;
    float height;
    Vector2 center;

public:
    Rectangle(float width, float height, Vector2& center):
            width(width), height(height), center(std::move(center)) {}
};
#endif  //  GAME_PHYSICS_H_
