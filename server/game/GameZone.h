#ifndef GAME_ZONE_H_
#define GAME_ZONE_H_

#include "../../common/utility.h"
#include "../../common/game_image.h"
class GameZone {
    public:
    virtual void move(player_id_t id, const Position& direction) = 0;
    virtual ~GameZone() = default;
};
#endif // GAME_ZONE_H_