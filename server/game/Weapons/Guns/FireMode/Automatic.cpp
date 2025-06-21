#include "Automatic.h"

#include <iostream>

Automatic::Automatic(const max_burst_t max_burst, const fire_rate_t fire_rate,
                     const burst_coldown_t burst_coldown):
        max_burst(max_burst),
        shot_timer(fire_rate),
        burst_timer(burst_coldown),
        bullets_in_burst(0),
        in_burst(false) {}

Automatic::~Automatic() {}


bool Automatic::can_fire() {
    if (!this->shot_timer.can_fire()) {
        return false;
    }
    this->shot_timer.start();
    return true;
}

bool Automatic::can_fire_burst() {
    if (!in_burst && !burst_timer.can_fire()) {
        return false;
    }
    if (in_burst && !shot_timer.can_fire()) {
        return false;
    }
    if (!in_burst) {
        in_burst = true;
        bullets_in_burst = 0;
    }
    std::cout << "Estoy disparando en rafaga para una automatica" << std::endl;
    bullets_in_burst++;
    shot_timer.start();

    if (bullets_in_burst >= max_burst) {
        in_burst = false;
        bullets_in_burst = 0;
        burst_timer.start();
    }
    return true;
}
