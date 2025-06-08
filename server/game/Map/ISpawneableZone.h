#ifndef I_SPAWNEABLE_ZONE_H_
#define I_SPAWNEABLE_ZONE_H_
#include <functional>
#include <memory>

#include "../Colliders/Colliders.h"

class ISpawneableZone {
public:
    typedef struct collider_solicitude_t {
        uint8_t width;
        uint8_t distance;
        Position& mouse_position;
        std::function<uint8_t(float)> damage_function;
    } collider_solicitude_t;
    virtual void spawn_collider(player_id_t id_spawn, collider_solicitude_t& wanted) = 0;
    virtual bool plant_bomb(const player_id_t& id_spawn) = 0;
    virtual ~ISpawneableZone() = default;
};
#endif  //  I_SPAWNEABLE_ZONE_H_
