#ifndef GAME_PHYSICS_H_
#define GAME_PHYSICS_H_
//  "Copyright 2025 Yaco Santamarina"
class Vector2 {
public:
  float x;
  float y;
  Vector2(float _x, float _y) : x(_x), y(_y) {}
  Vector2(Vector2 &&other) = default;
  Vector2(const Vector2 &) = default;
  Vector2 operator+(const Vector2 &other);
  Vector2 &operator+=(const Vector2 &other);
  Vector2 operator-(const Vector2 &other);
  Vector2 &operator-=(const Vector2 &other);
  Vector2 &operator=(Vector2 &&other) = default;
  Vector2 &operator=(const Vector2 &) = default;
};

#endif //  GAME_PHYSICS_H_
