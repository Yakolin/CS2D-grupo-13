#include "utility.h"
//  "Copyright 2025 Yaco Santamarina"
Position Position::operator+(const Position& other) const {
    return Position(this->x + other.x, this->y + other.y);
}
Position& Position::operator+=(const Position& other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}
Position Position::operator-(const Position& other) const {
    return Position(this->x - other.x, this->y - other.y);
}
Position& Position::operator-=(const Position& other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}
bool Position::operator==(const Position& other) const {
    return this->x == other.x && this->y == other.y;
}
bool Position::operator<(const Position& other) const {
    if (this->x == other.x)
        return this->y < other.y;
    return this->x < other.x;
}
