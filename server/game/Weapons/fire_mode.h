#ifndef FIRE_MODE_H
#define FIRE_MODE_H

#include "../Map/ISpawneableZone.h"

using max_burst_t = uint8_t;
using time_between_shoots_t = uint8_t;
using burst_coldown_t = uint8_t;

class FireMode {
public:
    virtual bool fire(ISpawneableZone& spawn, player_id_t id, ShootType& shoot_type,
                      Position& direction) = 0;

    virtual ~FireMode() = default;
};

class Automatic: public FireMode {

private:
    max_burst_t max_burst;
    time_between_shoots_t time_between_shoots;
    burst_coldown_t burst_coldown;

public:
    Automatic(const max_burst_t max_burst, const time_between_shoots_t time_between_shoots,
              const burst_coldown_t burst_coldown);
    ~Automatic();

    bool fire(ISpawneableZone& spawn, player_id_t id, ShootType& shoot_type,
              Position& direction) override;
};

class SemiAutomatic: public FireMode {
public:
    SemiAutomatic();
    ~SemiAutomatic();

    bool fire(ISpawneableZone& spawn, player_id_t id, ShootType& shoot_type,
              Position& direction) override;
};

#endif  // !FIRE_MODE_H