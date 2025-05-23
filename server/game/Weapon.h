#ifndef WEAPON_H_
#define WEAPON_H_
#include "../../common/player_command_types.h"

#include "Physics.h"
class Map;
class Weapon {
public:
    WeaponType type;
    virtual ~Weapon() = default;
    virtual void fire(Map& map, player_id_t id, Vector2& position,
                      Vector2& direction) = 0;  // Recordatorio de este = 0. Significa que es puro
    virtual void reload() = 0;

protected:
    explicit Weapon(WeaponType type): type(type) {}
};
#endif  //  WEAPON_H_
