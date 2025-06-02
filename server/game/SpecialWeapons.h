#ifndef SpecialWeapons_H_
#define SpecialWeapons_H_
#include "Weapon.h"

class Bomb {
public:
};

class Knife: public Weapon {
public:
    Knife(): Weapon(WeaponCode::KNIFE) {}
    virtual void set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual void reload() override;
    virtual WeaponImage get_weapon_image() override;
};

#endif  // SpecialWeapons_H_
