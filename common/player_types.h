#ifndef PLAYER_TYPES_H
#define PLAYER_TYPES_H

#include <cstdint>

using player_command_t = std::uint8_t;
using move_t = std::uint8_t;
using ammo_t = std::uint16_t;
using player_id_t = std::uint16_t;
using weapon_code_t = std::uint8_t;
using weapon_type_t = std::uint8_t;
using equip_type_t = std::uint8_t;

enum class PlayerCommandType {
    MOVE,
    BUY_WEAPON,
    BUY_AMMO,
    RELOAD,
    SHOOT,
    DROP,
    PLANT_BOMB,
    DEFUSE_BOMB,
    EQUIP
};

enum class MoveType { RIGHT, LEFT, UP, DOWN };

enum class WeaponType { PRIMARY, SECONDARY, KNIFE };

enum class WeaponCode { GLOCK, AK47, M3, AWP };

enum class EquipType {
    ROLL_DOWN,  // podria usar la ruedita
    ROLL_UP,
    PRIMARY,  // podria usar los numeros para cambiar armas
    SECONDARY,
    KNIFE
};

#endif  // !PLAYER_TYPES_H