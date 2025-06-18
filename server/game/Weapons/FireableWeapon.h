
#ifndef FIREABLE_WEAPON_H
#define FIREABLE_WEAPON_H

//  "Copyright 2025 Yaco Santamarina"

using fire_rate_t = uint8_t;
using magazine_t = uint8_t;
using bullet_t = uint8_t;
using width_t = uint8_t;
using distance_t = uint8_t;

class FireableWeapon {
protected:
    const bullet_t max_bullets;
    const magazine_t max_magazine;
    const fire_rate_t fire_rate;

    magazine_t actual_magazine;
    bullet_t actual_bullets;

    bool reduce_bullets();

public:
    FireableWeapon(bullet_t max_bullets, magazine_t magazine, fire_rate_t fire_rate);
    ~FireableWeapon();

    void reload();
    void restore_bullets();
};


#endif  // FIREABLE_WEAPON_H
