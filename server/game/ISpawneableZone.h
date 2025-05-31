#ifndef I_SPAWNEABLE_ZONE_H_
#define I_SPAWNEABLE_ZONE_H_
#include <memory>

#include "Colliders.h"

class ISpawneableZone {
public:
    typedef struct DamageCollider {
        uint8_t width;
        uint8_t distance;
        Position& direction;
    } damage_collider_t;
    virtual void spawn_collider(player_id_t id_spawn, damage_collider_t& wanted) = 0;
    virtual ~ISpawneableZone() = default;
};
#endif  //  I_SPAWNEABLE_ZONE_H_
