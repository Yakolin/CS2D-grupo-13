
#ifndef FIREABLE_WEAPON_H_
#define FIREABLE_WEAPON_H_

//  "Copyright 2025 Yaco Santamarina"
#include <algorithm>
#include <iostream>

#include "Bullet.h"
#include "Weapon.h"
class FireableWeapon: public Weapon {
private:
    int damage;
    int fire_rate;
    int max_bullets;
    int current_bullets;
    int magazine;

protected:
    FireableWeapon(WeaponType type, int dmg, int rate, int max_b, int current_b):
            Weapon(type),
            damage(dmg),
            fire_rate(rate),
            max_bullets(max_b),
            current_bullets(current_b),
            magazine(current_b) {}

public:
    virtual void fire(Vector2& position, Vector2& direction) override;
    virtual void reload() override;
};
class Ak47: public FireableWeapon {
public:
    Ak47(): FireableWeapon(WeaponType::PRIMARY, 25, 3, 90, 30) {}
};
class Glock: public FireableWeapon {
public:
    Glock(): FireableWeapon(WeaponType::SECONDARY, 15, 1, 120, 30) {}
};

#endif  // FIREABLE_WEAPON_H_
