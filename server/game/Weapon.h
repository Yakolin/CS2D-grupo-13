#ifndef WEAPON_H_
#define WEAPON_H_

#include <map>
#include <memory>

#include "../../common/player_command_types.h"
#include "Colliders.h"
class Weapon {
public:
    WeaponType type;
    virtual ~Weapon() = default;
    virtual void set_on_action(
            std::map<player_id_t, std::unique_ptr<Collider>>& damage_colliders, player_id_t id,
            Position& position,
            Position& direction) = 0;  // Recordatorio de este = 0. Significa que es puro
    virtual void reload() = 0;

protected:
    explicit Weapon(WeaponType type): type(type) {}
};
#endif  //  WEAPON_H_
