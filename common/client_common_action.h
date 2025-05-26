#ifndef CLIENT_COMMON_ACTION_H
#define CLIENT_COMMON_ACTION_H

#include <string>

#include "game_image.h"
#include "lobby_types.h"
#include "player_command_types.h"


/*
    LOBBY ACTIONS
*/

class CreateGameCommon {
protected:
    const std::string game_name;

public:
    explicit CreateGameCommon(const std::string& game_name): game_name(game_name) {}
    virtual ~CreateGameCommon() = default;
};

class JoinGameCommon {
protected:
    const std::string game_name;

public:
    explicit JoinGameCommon(const std::string& game_name): game_name(game_name) {}
    virtual ~JoinGameCommon() = default;
};


/*
    PLAYER ACTIONS
*/

class MoveCommon {
protected:
    const MoveType move_type;

public:
    explicit MoveCommon(MoveType move_type): move_type(move_type) {}
    virtual ~MoveCommon() = default;
};

class BuyWeaponCommon {
protected:
    const WeaponCode weapon_code;

public:
    explicit BuyWeaponCommon(WeaponCode weapon_code): weapon_code(weapon_code) {}
    virtual ~BuyWeaponCommon() = default;
};

class BuyAmmoCommon {
protected:
    const WeaponType weapon_type;
    const ammo_t ammo_count;

public:
    BuyAmmoCommon(WeaponType weapon_type, ammo_t ammo_count):
            weapon_type(weapon_type), ammo_count(ammo_count) {}
    virtual ~BuyAmmoCommon() = default;
};

class ShootCommon {
protected:
    const coordinate_t mouse_x;
    const coordinate_t mouse_y;

public:
    ShootCommon(coordinate_t mouse_x, coordinate_t mouse_y): mouse_x(mouse_x), mouse_y(mouse_y) {}
    virtual ~ShootCommon() = default;
};

class EquipCommon {
protected:
    const EquipType equip_type;

public:
    explicit EquipCommon(EquipType equip_type): equip_type(equip_type) {}
    virtual ~EquipCommon() = default;
};

#endif  // !CLIENT_COMMON_ACTION_H