#include "Physics.h"
//  "Copyright 2025 Yaco Santamarina"
Vector2 Vector2::operator+(const Vector2 &other) {
  return Vector2(this->x + other.x, this->y + other.y);
}
Vector2 &Vector2::operator+=(const Vector2 &other) {
  this->x += other.y;
  this->y += other.y;
  return *this;
}
Vector2 Vector2::operator-(const Vector2 &other) {
  return Vector2(this->x - other.x, this->y - other.y);
}
Vector2 &Vector2::operator-=(const Vector2 &other) {
  this->x -= other.y;
  this->y -= other.y;
  return *this;
}
