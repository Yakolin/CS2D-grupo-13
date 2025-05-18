#ifndef BULLET_H
#define BULLET_H

#include <utility>

#include "../common/player_command_types.h"

#include "Physics.h"
class Bullet {
public:
    bullet_id_t id;
    Vector2 position;
    Vector2 direction;
    float velocity;
    float damage;
    float size = 0.5f;
    Bullet(bullet_id_t id, Vector2 position, Vector2 direction, float velocity, float damage):
            id(id),
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
