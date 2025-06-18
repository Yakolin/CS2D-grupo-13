#ifndef KNIFE_H
#define KNIFE_H

#include "../Weapon.h"
#include "../fire_mode.h"

#include "weapon_config.h"

class Knife: public Weapon, public IInteractuable {
public:
    explicit Knife();

    ~Knife();

    bool set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) override;

    void reload() override;

    WeaponImage get_weapon_image() override;

    bool is_droppable() override;

    void reset() override;
};

#endif  // !KNIFE_H
