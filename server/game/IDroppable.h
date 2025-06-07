#ifndef DROPPABLE_H_
#define DROPPABLE_H_
#include "../../common/player_command_types.h"

class IDroppable {
public:
    WeaponCode code;
    explicit IDroppable(WeaponCode code): code(code) {}
    WeaponCode get_weapon_code() { return code; }
    virtual ~IDroppable() = 0;
};

#endif  // DROPPABLE_H_
