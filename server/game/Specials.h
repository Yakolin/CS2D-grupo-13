#ifndef SPECIALS_H_
#define SPECIALS_H_
#include "Weapon.h"

class Bomb {
public:
<<<<<<< HEAD:game/Specials.h
=======
    Bomb(): Weapon(WeaponType::BOMB) {}
    virtual void reload() override;
    virtual void fire(Map& map, player_id_t id, Vector2& position, Vector2& direction) override;
>>>>>>> origin/Server-Branch:server/game/Specials.h
};

class Knife {
public:
<<<<<<< HEAD:game/Specials.h
=======
    virtual void fire(Map& map, player_id_t id, Vector2& position, Vector2& direction) override;
    virtual void reload() override;
    Knife(): Weapon(WeaponType::KNIFE) {}
>>>>>>> origin/Server-Branch:server/game/Specials.h
};

#endif  // SPECIALS_H_
