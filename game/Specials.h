#ifndef SPECIALS_H_
#define SPECIALS_H_
#include "Weapon.h"


class Bomb: Weapon {
    virtual void fire() override;
};

class Knife: Weapon {
    virtual void fire() override;
};

#endif  // SPECIALS_H_
