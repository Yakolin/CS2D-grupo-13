#include "SemiAutomatic.h"

#include <iostream>

SemiAutomatic::SemiAutomatic(fire_rate_t fire_rate):
        fire_rate_timer(fire_rate), already_fired(false) {}

SemiAutomatic::~SemiAutomatic() {}


bool SemiAutomatic::can_fire() {
    this->already_fired = false;
    if (!this->fire_rate_timer.can_fire()) {
        return false;
    }
    return true;
}

bool SemiAutomatic::can_fire_burst() {
    if (this->already_fired)
        return false;
    if (!fire_rate_timer.can_fire())
        return false;
    fire_rate_timer.start();
    this->already_fired = true;
    return true;
}