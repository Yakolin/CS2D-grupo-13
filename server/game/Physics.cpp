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

/*
Vector2& Vector2::normalize() {
    float norm = get_norm();
    this->x = x / norm;
    this->y = y / norm;
    return *this;
}
*/

bool Vector2::operator==(const Vector2& other) const {
    return this->x == other.x && this->y == other.y;
}


/* RECTANGLE */

bool Rectangle::is_in(const Vector2& position) {
    bool x_in = point_min.x <= position.x && position.x <= point_max.x;
    bool y_in = point_min.y <= position.y && position.y <= point_max.y;
    return x_in && y_in;
}
