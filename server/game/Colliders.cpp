#include "Colliders.h"

Collider::~Collider() {}

bool Line::is_in(const Position& position) {
    float ab = start.distance(end);
    float ac = start.distance(position);
    float bc = end.distance(position);
    float diference = std::abs(ab - (ac + bc));
    return diference <= width;
}
bool Rectangle::is_in(const Position& position) {
    bool x_in = point_min.x <= position.x && position.x <= point_max.x;
    bool y_in = point_min.y <= position.y && position.y <= point_max.y;
    return x_in && y_in;
}
Position Rectangle::get_random_position() {
    uint16_t x = point_min.x + rand() % (point_max.x - point_min.x);
    uint16_t y = point_min.y + rand() % (point_max.y - point_min.y);
    return Position(x, y);
}
