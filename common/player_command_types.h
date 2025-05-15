#ifndef PLAYER_COMMAND_TYPES_H
#define PLAYER_COMMAND_TYPES_H

#include <cstdint>

using player_command_t = std::uint8_t;
using move_t = std::uint8_t;
using ammo_t = std::uint16_t;
using player_id_t = std::uint16_t;
using weapon_code_t = std::uint8_t;
using weapon_type_t = std::uint8_t;

enum class PlayerCommandType {
    MOVE,
    BUY_WEAPON,
    BUY_AMMO,
    RELOAD,
    SHOOT,
    DROP_WEAPON,
    PLANT_BOMB,
    DEFUSE_BOMB,
    DROP_BOMB
};

enum class MoveType {
    RIGHT,
    LEFT,
    UP,
    DOWN,
};

enum class WeaponType {
    PRIMARY,
    SECONDARY,
    KNIFE,
};

enum class WeaponCode { GLOCK, AK47, M3, AWP };

#endif  // !PLAYER_COMMAND_TYPES_H
