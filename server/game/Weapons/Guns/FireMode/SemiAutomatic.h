#ifndef SEMIAUTOMATIC_H
#define SEMIAUTOMATIC_H

#include "FireMode.h"
#include "FireRateClock.h"

class SemiAutomatic: public FireMode {
private:
    FireRateClock timer;
    bool already_fired;

public:
    explicit SemiAutomatic(timer_fire_t timer_fire);
    ~SemiAutomatic();

    bool can_fire() override;

    bool can_fire_burst() override;
};


#endif  // !SEMIAUTOMATIC_H
