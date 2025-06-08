
#ifndef FIREABLE_WEAPON_H_
#define FIREABLE_WEAPON_H_

//  "Copyright 2025 Yaco Santamarina"
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "Weapon.h"
class FireableWeapon: public Weapon {
public:
    FireableWeapon(WeaponCode code, weapon_specs_t specs): Weapon(code, specs) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override = 0;
    virtual void reload() override;
    virtual WeaponImage get_weapon_image() override;
};
class Ak47: public FireableWeapon {
private:
    uint8_t calculate_damage(float distance);

public:
    explicit Ak47(weapon_specs_t specs): FireableWeapon(WeaponCode::AK47, specs) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual bool is_droppable() override;
};
class Glock: public FireableWeapon {
private:
    uint8_t calculate_damage(float distance);

public:
    explicit Glock(weapon_specs_t specs): FireableWeapon(WeaponCode::GLOCK, specs) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual bool is_droppable() override;
};

class Knife: public Weapon {
public:
    explicit Knife(weapon_specs_t specs): Weapon(WeaponCode::KNIFE, specs) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual void reload() override;
    virtual WeaponImage get_weapon_image() override;
    virtual bool is_droppable() override;
};

#endif  // FIREABLE_WEAPON_H_
