#ifndef CLIENT_COMMON_ACTION_H
#define CLIENT_COMMON_ACTION_H

#include <string>

#include "lobby_types.h"
#include "player_types.h"


/*
    LOBBY ACTIONS
*/

class CreateGameCommon {
protected:
    const std::string game_name;

public:
    CreateGameCommon(const std::string& game_name): game_name(game_name) {}
    virtual ~CreateGameCommon() = default;
};

class JoinGameCommon {
protected:
    const std::string game_name;

public:
    JoinGameCommon(const std::string& game_name): game_name(game_name) {}
    virtual ~JoinGameCommon() = default;
};


/*
    PLAYER ACTIONS
*/

class MoveCommon {
protected:
    const MoveType move_type;

public:
    MoveCommon(MoveType move_type): move_type(move_type) {}
    virtual ~MoveCommon() = default;
};

class BuyWeaponCommon {
protected:
    const WeaponCode weapon_code;

public:
    BuyWeaponCommon(WeaponCode weapon_code): weapon_code(weapon_code) {}
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

class ReloadCommon {
protected:
    const WeaponType weapon_type;

public:
    ReloadCommon(WeaponType weapon_type): weapon_type(weapon_type) {}
    virtual ~ReloadCommon() = default;
};

class ShootCommon {
protected:
    const WeaponType weapon_type;
    const ammo_t ammo_count;

public:
    ShootCommon(WeaponType weapon_type, ammo_t ammo_count):
            weapon_type(weapon_type), ammo_count(ammo_count) {}
    virtual ~ShootCommon() = default;
};

class DropWeaponCommon {
protected:
    const WeaponType weapon_type;

public:
    DropWeaponCommon(WeaponType weapon_type): weapon_type(weapon_type) {}
    virtual ~DropWeaponCommon() = default;
};


#endif  // !CLIENT_COMMON_ACTION_H