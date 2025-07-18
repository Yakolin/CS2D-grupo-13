#ifndef INTERFACE_CAN_INTERACT_H_
#define INTERFACE_CAN_INTERACT_H_
#include <memory>

#include "../Weapons/SpecialWeapons.h"
#include "../Weapons/Weapon.h"
class ICanInteract {
public:
    virtual void damage(uint8_t damage) = 0;
    virtual bool is_dead() = 0;
    virtual bool equip(std::shared_ptr<IInteractuable>& droppable) = 0;
    virtual Team get_team() = 0;
    virtual void give_points() = 0;
    virtual ~ICanInteract() = default;
};
#endif  // INTERFACE_CAN_INTERACT_H_
