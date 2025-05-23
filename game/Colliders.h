

#ifndef COLLIDERS_H_
#define COLLIDERS_H_
#include <utility>

#include "Physics.h"
class Line {
    Vector2 position;
    Vector2 direction;
    uint8_t width;
    Line(Vector2 position, Vector2 direction, uint8_t width):
            position(position), direction(direction), width(width) {}
};

class Rectangle {
private:
    Vector2 point_min;
    Vector2 point_max;

public:
    Rectangle(coordinate_t width, coordinate_t height, const Vector2& point):
            point_min(std::move(point)),
            point_max(std::move(Vector2(point.x + width, point.y + height))) {}
    bool is_in(const Vector2& position);
};

class Circle {};

#endif  // COLLIDERS_H_
