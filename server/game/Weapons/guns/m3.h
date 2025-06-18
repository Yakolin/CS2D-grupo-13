#ifndef M3_H
#define M3_H

#include "../FireableWeapon.h"
#include "../Weapon.h"
#include "../fire_mode.h"

#include "weapon_config.h"

class M3: public Weapon, public FireableWeapon, public IInteractuable {
private:
    damage_t calculate_damage(float distance);

public:
    explicit M3();

    ~M3();

    bool set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) override;

    bool is_droppable() override;

    void reload() override;

    void reset() override;
};

#endif  // !M3_H