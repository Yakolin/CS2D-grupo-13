#ifndef SPECIALS_H_
#define SPECIALS_H_
#include "Weapon.h"

class Bomb {
public:
};

class Knife: public Weapon {
public:
    explicit Knife(WeaponCode code): Weapon(code) {}
    virtual void set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual void reload() override;
    virtual WeaponImage get_weapon_image() override;
};

#endif  // SPECIALS_H_
