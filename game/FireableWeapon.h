
#ifndef FIREABLE_WEAPON_H_
#define FIREABLE_WEAPON_H_

//  "Copyright 2025 Yaco Santamarina"
#include <algorithm>
#include <iostream>

#include "Bullet.h"
#include "Weapon.h"
class FireableWeapon: public Weapon {
protected:
    int damage;
    int fire_rate;
    int max_bullets;
    int current_bullets;
    int magazine;
    public:
    FireableWeapon(WeaponType type, int dmg, int rate, int max_b, int current_b):
            Weapon(type),
            damage(dmg),
            fire_rate(rate),
            max_bullets(max_b),
            current_bullets(current_b),
            magazine(current_b) {}
    // void reload_basic();
public:
    virtual void fire(Map& map, player_id_t id, Vector2& position, Vector2& direction) override = 0;
    virtual void reload() override;
};
class Ak47: public FireableWeapon {
public:
    Ak47(): FireableWeapon(WeaponType::PRIMARY, 25, 3, 90, 30) {}
    virtual void fire(Map& map, player_id_t id, Vector2& position, Vector2& direction) override;
    virtual void reload() override;
};
class Glock: public FireableWeapon {
public:
    Glock(): FireableWeapon(WeaponType::SECONDARY, 15, 1, 120, 30) {}
    virtual void fire(Map& map, player_id_t id, Vector2& position, Vector2& direction) override;
    virtual void reload() override;
};

#endif  // FIREABLE_WEAPON_H_
