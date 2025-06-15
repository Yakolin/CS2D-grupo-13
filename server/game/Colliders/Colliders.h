

#ifndef COLLIDERS_H_
#define COLLIDERS_H_
#include <utility>

#include "../../../common/utility.h"
class Vector2f {
public:
    float x;
    float y;
    float distance(const Vector2f& other) const;
    float norm();
    void normalize();
    Vector2f(float x, float y): x(x), y(y) {}
    ~Vector2f() = default;
};

class Collider {
public:
    virtual bool is_in(const Position& position) = 0;
    virtual ~Collider() = 0;
    virtual Vector2f get_end() = 0;
    virtual Vector2f get_start() = 0;
};

class Line: public Collider {
    Vector2f start;
    Vector2f end;
    uint8_t width;

public:
    Line(const Vector2f& start, const Vector2f& end, uint8_t width):
            start(std::move(start)), end(std::move(end)), width(width) {}
    float distance(Vector2f& other);
    Vector2f get_end() override { return end; }
    Vector2f get_start() override { return start; }
    virtual ~Line() override = default;
    virtual bool is_in(const Position& position) override;
};

class Rectangle: public Collider {

public:
    Position point_min;
    Position point_max;
    Rectangle() = default;

    Rectangle(coordinate_t width, coordinate_t height, const Position& point):
            point_min(std::move(point)),
            point_max(std::move(Position(point.x + width, point.y + height))) {}

    Rectangle(Position& point_min, Position& point_max):
            point_min(std::move(point_min)), point_max(std::move(point_max)) {}
    Rectangle& operator=(Rectangle&& other);
    virtual bool is_in(const Position& position) override;
    Position get_random_position();
    virtual ~Rectangle() override = default;
    Vector2f get_end() override { return Vector2f(point_max.x, point_max.y); }
    Vector2f get_start() override { return Vector2f(point_min.x, point_min.y); }
};

class Circle {};

#endif  // COLLIDERS_H_
