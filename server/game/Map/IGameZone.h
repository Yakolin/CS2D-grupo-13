#ifndef I_GAME_ZONE_H_
#define I_GAME_ZONE_H_

#include <utility>

#include "../../../common/game_image.h"
#include "../../../common/utility.h"
class IGameZone {
public:
    virtual bool move(player_id_t id, const Position& direction) = 0;
    virtual void defuse_bomb(const player_id_t& player_id) = 0;
    virtual ~IGameZone() = default;
};
#endif  // GAME_ZONE_H_
