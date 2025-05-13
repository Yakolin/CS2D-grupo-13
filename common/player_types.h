#ifndef PLAYER_TYPES_H
#define PLAYER_TYPES_H

#include <cstdint>

using ammo_t = std::uint16_t;

enum class PlayerCommandType
{
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    MOVE_DOWN,
    BUY_WEAPON,
    BUY_AMMO,
    RELOAD,
    SHOOT,
    DROP_WEAPON,
    PLANT_BOMB,
    DEFUSE_BOMB,
    DROP_BOMB
};

enum class WeaponType
{
    PRIMARY,
    SECONDARY,
    KNIFE,
};

enum class WeaponCode
{
    GLOCK,
    AK47,
    M3,
    AWP
};

#endif // !PLAYER_TYPES_H