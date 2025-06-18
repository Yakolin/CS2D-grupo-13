#ifndef SEMIAUTOMATIC_H
#define SEMIAUTOMATIC_H

#include "FireMode.h"

class SemiAutomatic: public FireMode {
public:
    SemiAutomatic();
    ~SemiAutomatic();

    bool fire(ISpawneableZone& spawn, player_id_t id, Position& direction) override;

    bool fire_burst(ISpawneableZone& spawn, player_id_t id, Position& direction) override;
};


#endif  // !SEMIAUTOMATIC_H