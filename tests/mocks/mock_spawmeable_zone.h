#ifndef MOCK_SPAWMEABLE_ZONE_H
#define MOCK_SPAWMEABLE_ZONE_H

#include <gmock/gmock.h>

#include "../../server/game/ISpawneableZone.h"

class MockISpawneableZone: public ISpawneableZone {
public:
    MOCK_METHOD(void, spawn_collider, (player_id_t id_spawn, damage_collider_t& wanted),
                (override));
};


#endif  // !MOCK_SPAWMEABLE_ZONE_H