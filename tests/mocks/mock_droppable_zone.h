#ifndef MOCK_DROPPABLE_ZONE_H
#define MOCK_DROPPABLE_ZONE_H

#include <gmock/gmock.h>

#include "../../server/game/IDropeableZone.h"

class MockIDroppableZone: public IDroppableZone {
public:
    MOCK_METHOD(void, drop, (const player_id_t& player_id, std::shared_ptr<IDroppable>& dropeable),
                (override));
    MOCK_METHOD(bool, plant_bomb, (const player_id_t& player_id), (override));
};

#endif  // !MOCK_DROPPBLE_ZONE_H