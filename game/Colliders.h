

#ifndef COLLIDERS_H_
#define COLLIDERS_H_
#include <utility>

#include "Physics.h"
class Collider {
public:
    virtual bool is_in(const Vector2& position) = 0;
    virtual ~Collider() = 0;
};
class Line: public Collider {
    Vector2 start;
    Vector2 end;
    uint8_t width;

public:
    Line(Vector2 start, Vector2 end, uint8_t width): start(start), end(end), width(width) {}
    virtual ~Line() override = default;
    virtual bool is_in(const Vector2& position) override;
};

class Rectangle: public Collider {
private:
    Vector2 point_min;
    Vector2 point_max;

public:
    Rectangle(coordinate_t width, coordinate_t height, const Vector2& point):
            point_min(std::move(point)),
            point_max(std::move(Vector2(point.x + width, point.y + height))) {}
    bool is_in(const Vector2& position) override;
    virtual ~Rectangle() override = default;
};

class Circle {};

#endif  // COLLIDERS_H_
