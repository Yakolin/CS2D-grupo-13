#include "Colliders.h"

Collider::~Collider() {}
float Vector2f::distance(const Vector2f& other) const {
    float dx = x - other.x;
    float dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}
float Vector2f::norm() { return sqrt(x * x + y * y); }
void Vector2f::normalize() {
    float norm_f = norm();
    if (norm_f == 0)
        return;
    x = x / norm_f;
    y = y / norm_f;
}
bool Line::is_in(const Position& position) {
    Vector2f aux(position.x, position.y);
    float ab = start.distance(end);
    float ac = start.distance(aux);
    float bc = end.distance(aux);
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
Rectangle& Rectangle::operator=(Rectangle&& other) {
    this->point_max = std::move(other.point_max);
    this->point_min = std::move(other.point_max);
    return *this;
}
