#ifndef FIRE_MODE_H
#define FIRE_MODE_H

#include "../../../Map/ISpawneableZone.h"

using max_burst_t = uint8_t;
using time_between_shoots_t = uint8_t;
using burst_coldown_t = uint8_t;

class FireMode {
public:
    virtual bool fire(ISpawneableZone& spawn, player_id_t id, Position& direction) = 0;

    virtual bool fire_burst(ISpawneableZone& spawn, player_id_t id, Position& direction) = 0;
    virtual ~FireMode() = default;
};


#endif  // !FIRE_MODE_H