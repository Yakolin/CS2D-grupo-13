#include "SemiAutomatic.h"

SemiAutomatic::SemiAutomatic(fire_rate_t fire_rate): timer(fire_rate) {}

SemiAutomatic::~SemiAutomatic() {}


bool SemiAutomatic::can_fire() {
    if (!this->fire_rate_timer.can_fire()) {
        return false;
    }
    return true;
}

bool SemiAutomatic::can_fire_burst() {
    if (!this->fire_rate_timer.can_fire()) {
        return false;
    }
    fire_rate_timer.start();
    return true;
}