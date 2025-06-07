#ifndef CLIENT_COMMON_ACTION_H
#define CLIENT_COMMON_ACTION_H

#include <string>

#include "game_image.h"
#include "lobby_types.h"
#include "player_command_types.h"


/*
    PLAYER ACTIONS
*/

class MoveCommon {
protected:
    MoveType move_type;

public:
    explicit MoveCommon(MoveType& move_type): move_type(move_type) {}
    virtual ~MoveCommon() = default;
};

class BuyWeaponCommon {
protected:
    WeaponCode weapon_code;

public:
    explicit BuyWeaponCommon(WeaponCode& weapon_code): weapon_code(weapon_code) {}
    virtual ~BuyWeaponCommon() = default;
};

class BuyAmmoCommon {
protected:
    WeaponType weapon_type;
    ammo_t ammo_count;

public:
    explicit BuyAmmoCommon(WeaponType& weapon_type, ammo_t& ammo_count):
            weapon_type(weapon_type), ammo_count(ammo_count) {}
    virtual ~BuyAmmoCommon() = default;
};

class ShootCommon {
protected:
    coordinate_t mouse_x;
    coordinate_t mouse_y;

public:
    explicit ShootCommon(coordinate_t& mouse_x, coordinate_t& mouse_y):
            mouse_x(mouse_x), mouse_y(mouse_y) {}
    virtual ~ShootCommon() = default;
};

class EquipCommon {
protected:
    EquipType equip_type;

public:
    explicit EquipCommon(EquipType& equip_type): equip_type(equip_type) {}
    virtual ~EquipCommon() = default;
};

class MousePositionCommon {
protected:
    coordinate_t mouse_x;
    coordinate_t mouse_y;

public:
    explicit MousePositionCommon(coordinate_t& mouse_x, coordinate_t& mouse_y):
            mouse_x(mouse_x), mouse_y(mouse_y) {}
    virtual ~MousePositionCommon() = default;
};

#endif  // !CLIENT_COMMON_ACTION_H
