#ifndef WEAPON_H_
#define WEAPON_H_
#include "../common/player_command_types.h"
class Weapon {
public:
    WeaponType type;
    ~Weapon() = default;
    virtual void fire() = 0;  // Recordatorio de este = 0. Significa que es puro
    virtual void reload() = 0;

protected:
    explicit Weapon(WeaponType type): type(type) {}
};
#endif  //  WEAPON_H_
