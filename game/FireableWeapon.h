
#ifndef FIREABLE_WEAPON_H_
#define FIREABLE_WEAPON_H_

//  "Copyright 2025 Yaco Santamarina"
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "Weapon.h"
class FireableWeapon: public Weapon {

protected:
    uint8_t damage;
    uint8_t fire_rate;
    uint8_t max_bullets;
    uint8_t current_bullets;
    uint8_t magazine;

public:
    FireableWeapon(WeaponType type, uint8_t dmg, uint8_t rate, uint8_t max_b, uint8_t current_b):
            Weapon(type),
            damage(dmg),
            fire_rate(rate),
            max_bullets(max_b),
            current_bullets(current_b),
            magazine(current_b) {}
    // void reload_basic();
    virtual void set_on_action(std::vector<Bullet>& bullets, player_id_t id, Vector2& position,
                               Vector2& direction) override = 0;
    virtual void reload() override;
};
class Ak47: public FireableWeapon {
public:
    Ak47(): FireableWeapon(WeaponType::PRIMARY, 25, 3, 90, 30) {}
    virtual void set_on_action(std::vector<Bullet>& bullets, player_id_t id, Vector2& position,
                               Vector2& direction) override;
};
class Glock: public FireableWeapon {
public:
    Glock(): FireableWeapon(WeaponType::SECONDARY, 15, 1, 120, 30) {}
    virtual void set_on_action(std::vector<Bullet>& bullets, player_id_t id, Vector2& position,
                               Vector2& direction) override;
};

#endif  // FIREABLE_WEAPON_H_
