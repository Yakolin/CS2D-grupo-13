#ifndef GLOCK_H
#define GLOCK_H

#include "../FireableWeapon.h"
#include "../Weapon.h"
#include "../fire_mode.h"

#include "weapon_config.h"
class Glock: public Weapon, public FireableWeapon, public IInteractuable {
private:
    damage_t calculate_damage(float distance);

public:
    explicit Glock();
    ~Glock();

    bool set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) override;
    bool is_droppable() override;

    void reset() override;
};


#endif  // !GLOCK_H
