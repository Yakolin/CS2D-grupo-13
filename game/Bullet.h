#ifndef BULLET_H
#define BULLET_H

#include <utility>

#include "Physics.h"
class Bullet {
public:
    Vector2 position;
    Vector2 direction;
    float velocity;
    float damage;
    Bullet(Vector2 position, Vector2 direction, float velocity, float damage):
            position(std::move(position)),
            direction(std::move(direction)),
            velocity(velocity),
            damage(damage) {}
    void move() {
        position.x += direction.x * velocity;
        position.y += direction.y * velocity;
    }
};

#endif  // !BULLET_H
