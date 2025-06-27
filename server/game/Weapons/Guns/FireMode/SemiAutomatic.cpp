#include "SemiAutomatic.h"

#include <iostream>

SemiAutomatic::SemiAutomatic(timer_fire_t timer_fire): timer(timer_fire), already_fired(false) {}

SemiAutomatic::~SemiAutomatic() {}


bool SemiAutomatic::can_fire() {
    this->already_fired = false;
    if (!this->timer.can_fire()) {
        return false;
    }
    this->timer.start();
    return true;
}

bool SemiAutomatic::can_fire_burst() {
    if (this->already_fired)
        return false;
    if (!timer.can_fire())
        return false;
    timer.start();
    this->already_fired = true;
    return true;
}