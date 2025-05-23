#ifndef SPECIALS_H_
#define SPECIALS_H_
#include "Weapon.h"

class Bomb: public Weapon {
public:
    Bomb(): Weapon(WeaponType::BOMB) {}
    virtual void reload() override;
    virtual void fire(Map& map, player_id_t id, Vector2& position, Vector2& direction) override;
};

class Knife: public Weapon {
public:
    virtual void fire(Map& map, player_id_t id, Vector2& position, Vector2& direction) override;
    virtual void reload() override;
    Knife(): Weapon(WeaponType::KNIFE) {}
};

#endif  // SPECIALS_H_
