#ifndef AK_H
#define AK_H

#include <chrono>

#include "../../Config/GameConfig.h"
#include "../FireableWeapon.h"
#include "FireMode/Automatic.h"

#include "BurstClock.h"

class Ak47: public FireableWeapon {

private:
    uint8_t calculate_damage(float distance);

public:
    explicit Ak47(GameConfig::weapon_config_t specs);
    ~Ak47();
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual bool is_droppable() override;
};

#endif  // !AK_H