#ifndef SEMIAUTOMATIC_H
#define SEMIAUTOMATIC_H

#include "FireMode.h"
#include "FireRateClock.h"

class SemiAutomatic: public FireMode {
private:
    FireRateClock fire_rate_timer;

public:
    SemiAutomatic(fire_rate_t fire_rate);
    ~SemiAutomatic();

    bool can_fire() override;

    bool can_fire_burst() override;
};


#endif  // !SEMIAUTOMATIC_H