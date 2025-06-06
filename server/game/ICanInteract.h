#ifndef INTERFACE_CAN_INTERACT_H_
#define INTERFACE_CAN_INTERACT_H_
#include <memory>

#include "SpecialWeapons.h"
#include "Weapon.h"
class ICanInteract {
public:
    virtual void damage(uint8_t damage) = 0;
    virtual bool equip_weapon(std::unique_ptr<Weapon>& weapon) = 0;
    virtual void equip_bomb(std::weak_ptr<Bomb> bomb) = 0;
    virtual ~ICanInteract() = default;
};
#endif  // INTERFACE_CAN_INTERACT_H_
