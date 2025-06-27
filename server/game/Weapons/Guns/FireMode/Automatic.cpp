#include "Automatic.h"

#include <iostream>

Automatic::Automatic(const max_burst_t max_burst, const timer_fire_t timer_fire,
                     const burst_coldown_t burst_coldown):
        max_burst(max_burst),
        shot_timer(timer_fire),
        burst_timer(burst_coldown),
        bullets_in_burst(0),
        in_burst(false) {}

Automatic::~Automatic() {}


bool Automatic::can_fire() {
    if (!in_burst) {
        if (burst_timer.can_fire()) {
            in_burst = true;
            bullets_in_burst = 0;
            shot_timer.reset();
        } else {
            return false;
        }
    }
    if (shot_timer.can_fire()) {
        shot_timer.start();
        bullets_in_burst++;

        if (bullets_in_burst >= max_burst) {
            in_burst = false;
            bullets_in_burst = 0;
            burst_timer.start();
        }

        return true;
    }

    return false;
}

bool Automatic::can_fire_burst() { return can_fire(); }
