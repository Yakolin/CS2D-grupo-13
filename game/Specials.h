#ifndef SPECIALS_H_
#define SPECIALS_H_
#include "Weapon.h"


class Bomb: Weapon {
public:
    Bomb(): Weapon(WeaponType::BOMB) {}
    virtual void fire() override;
};

class Knife: Weapon {
public:
    virtual void fire() override;
    Knife(): Weapon(WeaponType::KNIFE) {}
};

#endif  // SPECIALS_H_
