#include "Automatic.h"

Automatic::Automatic(const max_burst_t max_burst, const time_between_shoots_t time_between_shoots,
                     const burst_coldown_t burst_coldown):
        bullets_in_burst(0),
        burst_timer(),
        shot_timer(),
        max_burst(max_burst),
        time_between_shoots(time_between_shoots),
        burst_coldown(burst_coldown) {}

Automatic::~Automatic() {}


bool Automatic::fire(ISpawneableZone& spawn, player_id_t id Position& direction) { return true; }

bool Automatic::fire_burst(ISpawneableZone& spawn, player_id_t id, Position& position) {
    return true;
}
