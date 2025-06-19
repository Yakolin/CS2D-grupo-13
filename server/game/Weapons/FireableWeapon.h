
#ifndef FIREABLE_WEAPON_H_
#define FIREABLE_WEAPON_H_

//  "Copyright 2025 Yaco Santamarina"

#include "../../../common/game_image.h"

#include "Weapon.h"

using magazine_t = uint8_t;
using bullet_t = uint8_t;

class FireableWeapon: public Weapon {

private:
    void shoot_common(ISpawneableZone& spawn, player_id_t id, Position& direction);

protected:
    const bullet_t max_bullets;
    const magazine_t max_magazine;

    bullet_t actual_bullets;
    magazine_t actual_magazine;

    virtual damage_t calculate_damage() override = 0;

public:
    FireableWeapon(WeaponCode weapon_code, damage_t damage, range_t range, width_t width,
                   std::unique_ptr<FireMode>&& fire_mode, bullet_t max_bullets,
                   magazine_t max_magazine);

    virtual ~FireableWeapon();

    void reduce_bullets();

    void restart();

    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;

    virtual bool shoot_burst(ISpawneableZone& spawn, player_id_t id, Position& direction) override;

    void reload() override;

    virtual bool is_droppable() override = 0;

    WeaponImage get_weapon_image() override;
};


#endif  // FIREABLE_WEAPON_H_
