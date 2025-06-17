#ifndef AK_H
#define AK_H

#include <chrono>

#include "../../Config/GameConfig.h"
#include "../FireableWeapon.h"

#include "BurstClock.h"

class Ak47: public FireableWeapon {

private:
    int bullets_in_burst = 0;
    BurstClock burst_timer;
    BurstClock shot_timer;
    // esto deberia de ser configurable por Yaml de igual forma.
    const int max_burst = 3;
    const float time_between_shoots = 0.4f;
    const float burst_coldown = 1.8f;

    uint8_t calculate_damage(float distance);

public:
    explicit Ak47(GameConfig::weapon_config_t specs);
    ~Ak47();
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual bool is_droppable() override;
};

#endif  // !AK_H