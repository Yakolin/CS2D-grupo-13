#ifndef I_SPAWNEABLE_ZONE_H_
#define I_SPAWNEABLE_ZONE_H_
#include <functional>
#include <memory>

#include "../Colliders/Colliders.h"

class ISpawneableZone {
public:
    typedef struct ColliderSolicitude {
        uint8_t width;
        uint8_t distance;
        uint8_t chance_hit;
        WeaponCode code;
        Position& mouse_position;
        std::function<damage_t(float)> damage_function;
    } collider_solicitude_t;
    virtual void spawn_collider(player_id_t id_spawn, collider_solicitude_t& wanted) = 0;
    virtual bool plant_bomb(const player_id_t& id_spawn) = 0;
    virtual ~ISpawneableZone() = default;
};
#endif  //  I_SPAWNEABLE_ZONE_H_
