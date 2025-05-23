#include "Colliders.h"

Collider::~Collider() {}

bool Line::is_in(const Vector2& position) {
    float ab = start.distance(end);
    float ac = start.distance(position);
    float bc = end.distance(position);
    float diference = std::abs(ab - (ac + bc));
    return diference <= width;
}
bool Rectangle::is_in(const Vector2& position) {
    bool x_in = point_min.x <= position.x && position.x <= point_max.x;
    bool y_in = point_min.y <= position.y && position.y <= point_max.y;
    return x_in && y_in;
}
