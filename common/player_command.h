#ifndef PLAYER_COMMAND_H
#define PLAYER_COMMAND_H

enum class PlayerCommand
{
    BUY,
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

#endif // !PLAYER_COMMAND_H