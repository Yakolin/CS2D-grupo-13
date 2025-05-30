#ifndef I_SPAWNEABLE_ZONE_H_
#define I_SPAWNEABLE_ZONE_H_
#include "Colliders.h"

class ISpawneableZone {
    virtual void spawn_collider(Collider& collider, uint8_t times /* Algo mas)?*/) = 0;
};
#endif  //  I_SPAWNEABLE_ZONE_H_
