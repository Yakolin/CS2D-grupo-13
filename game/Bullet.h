#ifndef BULLET_H
#define BULLET_H

#include <utility>

#include "Physics.h"
class Bullet {
public:
    Vector2 position;
    Vector2 direction;
    float velocity;
    Bullet(Vector2&& position, Vector2&& direction, float velocity):
            position(std::move(position)), direction(std::move(direction)), velocity(velocity) {}
    void move() {
        position.x += direction.x * velocity;
        position.y += direction.y * velocity;
    }
};

#endif  // !BULLET_H
