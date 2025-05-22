#ifndef CLIENT_COMMON_ACTION_H
#define CLIENT_COMMON_ACTION_H

#include <string>

#include "lobby_types.h"
#include "player_command_types.h"
#include "utility.h"


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

class ShootCommon {
protected:
    const Position position;
    const ammo_t ammo_count;

public:
    ShootCommon(Position position, ammo_t ammo_count): position(position), ammo_count(ammo_count) {}
    virtual ~ShootCommon() = default;
};

class EquipCommon {
protected:
    const EquipType equip_type;

public:
    EquipCommon(EquipType equip_type): equip_type(equip_type) {}
    virtual ~EquipCommon() = default;
};

#endif  // !CLIENT_COMMON_ACTION_H
#ifndef CLIENT_COMMON_ACTION_H
#define CLIENT_COMMON_ACTION_H

#include <string>

#include "lobby_types.h"
#include "player_types.h"
#include "utility.h"


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

class ShootCommon {
protected:
    const Position position;
    const ammo_t ammo_count;

public:
    ShootCommon(Position position, ammo_t ammo_count): position(position), ammo_count(ammo_count) {}
    virtual ~ShootCommon() = default;
};

class EquipCommon {
protected:
    const EquipType equip_type;

public:
    EquipCommon(EquipType equip_type): equip_type(equip_type) {}
    virtual ~EquipCommon() = default;
};

#endif  // !CLIENT_COMMON_ACTION_H