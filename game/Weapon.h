#ifndef WEAPON_H_
#define WEAPON_H_
#include <vector>

#include "../common/player_command_types.h"

#include "Bullet.h"
#include "Physics.h"
class Weapon {
public:
    WeaponType type;
    virtual ~Weapon() = default;
    virtual void set_on_action(
            std::vector<Bullet>& bullets, player_id_t id, Vector2& position,
            Vector2& direction) = 0;  // Recordatorio de este = 0. Significa que es puro
    virtual void reload() = 0;

protected:
    explicit Weapon(WeaponType type): type(type) {}
};
#endif  //  WEAPON_H_
