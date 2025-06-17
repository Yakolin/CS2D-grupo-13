
#ifndef FIREABLE_WEAPON_H_
#define FIREABLE_WEAPON_H_

//  "Copyright 2025 Yaco Santamarina"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "Weapon.h"
class FireableWeapon: public Weapon {
    max_bullets_t inventory_bullets;
    max_bullets_t magazine;

protected:
    bool reduce_bullets();

public:
    FireableWeapon(WeaponCode code, GameConfig::weapon_config_t specs):
            Weapon(code, specs), inventory_bullets(specs.max_b), magazine(specs.current_b) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override = 0;
    virtual void reload() override;
    virtual void restore_bullets() override;
    virtual WeaponImage get_weapon_image() override;
};


#endif  // FIREABLE_WEAPON_H_
