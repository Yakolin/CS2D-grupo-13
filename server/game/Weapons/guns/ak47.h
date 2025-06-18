#ifndef AK_H
#define AK_H

#include <chrono>

#include "../FireableWeapon.h"
#include "../Weapon.h"
#include "../fire_mode.h"

#include "weapon_config.h"

using max_burst_t = uint8_t;
using time_between_shoots_t = float;
using burst_coldown_t = float;

class Ak47: public Weapon, public FireableWeapon, public IInteractuable {

private:
    bullet_t bullets_in_burst;
    const max_burst_t max_burst;
    const time_between_shoots_t time_between_shoots;
    const burst_coldown_t burst_coldown;

    damage_t calculate_damage(float distance);

public:
    explicit Ak47();
    ~Ak47();
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual bool is_droppable() override;
};

#endif  // !AK_H