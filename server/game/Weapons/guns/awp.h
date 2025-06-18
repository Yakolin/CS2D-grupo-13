#ifndef AWP_H
#define AWP_H

#include "../FireableWeapon.h"
#include "../Weapon.h"
#include "../fire_mode.h"

#include "weapon_config.h"

class Awp: public Weapon, public FireableWeapon, public IInteractuable {
private:
    damage_t calculate_damage(float distance);

public:
    explicit Awp();
    ~Awp();

    bool set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) override;


    bool is_droppable() override;

    void reset() override;
};

#endif  // !AWP_H