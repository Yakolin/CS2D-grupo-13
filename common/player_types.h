#ifndef PLAYER_TYPES_H
#define PLAYER_TYPES_H

using ammo_t = uint16_t;

enum class PlayerCommandType
{
    BUY_AMMO,
    BUY_WEAPON,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    MOVE_DOWN,
    RELOAD,
    SHOOT,
    PLANT_BOMB,
    DEFUSE_BOMB,
    DROP_WEAPON,
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