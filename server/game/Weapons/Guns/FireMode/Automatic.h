#ifndef AUTOMATIC_H
#define AUTOMATIC_H


#include "BurstClock.h"
#include "FireMode.h"
#include "FireRateClock.h"

using bullet_t = uint8_t;
using max_burst_t = uint8_t;

class Automatic: public FireMode {
private:
    const max_burst_t max_burst;
    FireRateClock shot_timer;
    BurstClock burst_timer;

    bullet_t bullets_in_burst;
    bool in_burst;

public:
    Automatic(const max_burst_t max_burst, const timer_fire_t timer_fire,
              const burst_coldown_t burst_coldown);
    ~Automatic();

    bool can_fire() override;

    bool can_fire_burst() override;
};


#endif  // !AUTOMATIC_H