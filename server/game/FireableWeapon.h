
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

protected:
    uint16_t price;
    uint8_t fire_rate;
    uint8_t max_bullets;
    uint8_t current_bullets;
    uint8_t magazine;

public:
    FireableWeapon(WeaponType type, uint16_t price, uint8_t rate, uint8_t max_b, uint8_t current_b):
            Weapon(type),
            price(price),
            fire_rate(rate),
            max_bullets(max_b),
            current_bullets(current_b),
            magazine(current_b) {}
    virtual void set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override = 0;
    virtual void reload() override;
};
class Ak47: public FireableWeapon {
public:
    Ak47(): FireableWeapon(WeaponType::PRIMARY, 2700, 3, 90, 30) {}
    virtual void set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
};
class Glock: public FireableWeapon {
public:
    Glock(): FireableWeapon(WeaponType::SECONDARY, 500, 1, 120, 30) {}
    virtual void set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
};

#endif  // FIREABLE_WEAPON_H_
