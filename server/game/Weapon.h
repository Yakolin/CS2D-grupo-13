#ifndef WEAPON_H_
#define WEAPON_H_

#include <map>
#include <memory>

#include "../../common/game_image.h"
#include "../../common/player_command_types.h"

#include "Colliders.h"
#include "ISpawneableZone.h"

class Weapon {
public:
    WeaponCode code;
    virtual void set_on_action(
            ISpawneableZone& spawn, player_id_t id,
            Position& direction) = 0;  // Recordatorio de este = 0. Significa que es puro
    virtual void reload() = 0;
    virtual WeaponImage get_weapon_image() = 0;
    explicit Weapon(WeaponCode code): code(code) {}
    virtual ~Weapon() = default;
    virtual bool is_droppable() = 0;
};

#endif  //  WEAPON_H_
