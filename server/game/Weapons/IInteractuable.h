#ifndef DROPPABLE_H_
#define DROPPABLE_H_
#include "../../../common/player_command_types.h"
#include "../Colliders/Colliders.h"
#include "../Map/ISpawneableZone.h"
class IInteractuable {
public:
    WeaponCode code;
    explicit IInteractuable(WeaponCode code): code(code) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) = 0;
    virtual bool shoot_burst(ISpawneableZone& spawn, player_id_t, Position& direction) = 0;
    WeaponCode get_weapon_code() { return code; }
    virtual bool reload() = 0;
    virtual bool have_bullets() = 0;
    virtual ~IInteractuable() = default;
};

#endif  // DROPPABLE_H_
