#ifndef AUTOMATIC_H
#define AUTOMATIC_H

#include "../BurstClock.h"

#include "FireMode.h"

class Automatic: public FireMode {
private:
    int bullets_in_burst;
    BurstClock burst_timer;
    BurstClock shot_timer;
    const max_burst_t max_burst;
    const time_between_shoots_t time_between_shoots;
    const burst_coldown_t burst_coldown;

public:
    Automatic(const max_burst_t max_burst, const time_between_shoots_t time_between_shoots,
              const burst_coldown_t burst_coldown);
    ~Automatic();

    bool fire(ISpawneableZone& spawn, player_id_t id, Position& direction) override;

    bool fire_burst(ISpawneableZone& spawn, player_id_t id, Position& direction) override;
};


#endif  // !AUTOMATIC_H