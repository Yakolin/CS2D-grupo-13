#include "fire_mode.h"


Automatic::Automatic(const max_burst_t max_burst, const time_between_shoots_t time_between_shoots,
                     const burst_coldown_t burst_coldown):
        max_burst(max_burst),
        time_between_shoots(time_between_shoots),
        burst_coldown(burst_coldown) {}

Automatic::~Automatic() {}


bool Automatic::fire(ISpawneableZone& spawn, player_id_t id, ShootType& shoot_type,
                     Position& direction) override {
    if (shoot_type == ShootType::HOLD) {
        return true;
    }
    if (shoot_type == ShootType::SINGLE_SHOT) {
        return true;
    } else {
        return false;
    }
}

SemiAutomatic::SemiAutomatic() {}

SemiAutomatic::~SemiAutomatic() {}


bool SemiAutomatic::fire(ISpawneableZone& spawn, player_id_t id, ShootType& shoot_type,
                         Position& direction) override {
    if (shoot_type == ShootType::HOLD) {
        return true;
    }
    if (shoot_type == ShootType::SINGLE_SHOT) {
        return true;
    } else {
        return false;
    }
}