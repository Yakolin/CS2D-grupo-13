#include "Physics.h"
//  "Copyright 2025 Yaco Santamarina"
Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(this->x + other.x, this->y + other.y);
}
Vector2& Vector2::operator+=(const Vector2& other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}
Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(this->x - other.x, this->y - other.y);
}
Vector2& Vector2::operator-=(const Vector2& other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

float Vector2::get_norm() const { return sqrt(x * x + y * y); }

Vector2& Vector2::normalize() {
    float norm = get_norm();
    this->x = x / norm;
    this->y = y / norm;
    return *this;
}

bool Vector2::operator==(const Vector2& other) const {
    return this->x == other.x && this->y == other.y;
}
