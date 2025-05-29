

#ifndef COLLIDERS_H_
#define COLLIDERS_H_
#include <utility>

#include "../../common/utility.h"
class Collider {
public:
    virtual bool is_in(const Position& position) = 0;
    virtual ~Collider() = 0;
};
class Line: public Collider {
    Position start;
    Position end;
    uint8_t width;

public:
    Line(Position start, Position end, uint8_t width): start(start), end(end), width(width) {}
    virtual ~Line() override = default;
    virtual bool is_in(const Position& position) override;
};

class Rectangle: public Collider {
private:
    Position point_min;
    Position point_max;

public:
    Rectangle() = default;
    Rectangle(coordinate_t width, coordinate_t height, const Position& point):
            point_min(std::move(point)),
            point_max(std::move(Position(point.x + width, point.y + height))) {}
    Rectangle(Position& point_min, Position& point_max);
    virtual bool is_in(const Position& position) override;
    Position get_random_position();
    virtual ~Rectangle() override = default;
};

class Circle {};

#endif  // COLLIDERS_H_
