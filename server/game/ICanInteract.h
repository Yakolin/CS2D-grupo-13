#ifndef INTERFACE_CAN_INTERACT_H_
#define INTERFACE_CAN_INTERACT_H_
#include "Weapon.h"

class CanInteract {
public:
    virtual void damage(uint8_t damage) = 0;
    // virtual void equip(std::unique_ptr<Weapon>& weapon) = 0;
    virtual ~CanInteract() = default;
};
#endif  // INTERFACE_CAN_INTERACT_H_
