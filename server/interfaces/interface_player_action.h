#ifndef INTERFACE_PLAYER_H
#define INTERFACE_PLAYER_H

#include <utility>

#include "../../common/player_command_types.h"
class IPlayerAction {
public:
    IPlayerAction() {}
    virtual ~IPlayerAction() = default;

    virtual void move(const MoveType& move_type) = 0;
    virtual void reload() = 0;
    virtual void shoot(const coordinate_t& mouse_x, const coordinate_t& mouse_y) = 0;
    virtual void buy_weapon(const WeaponCode& weapon_code) = 0;
    virtual void drop() = 0;
    virtual void equip(const EquipType& equip) = 0;
    /*
    virtual void defuse_bomb() = 0;
    virtual void buy_ammo(const WeaponType& weapon_type, const ammo_t& ammo_count) = 0;
    virtual void watch(const coordinate_t& mouse_x, const coordinate_t& mouse_y) = 0;
    */
};

#endif  // !INTERFACE_PLAYER_H
