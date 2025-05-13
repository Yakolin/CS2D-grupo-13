#ifndef PLAYER_ACTION_H
#define PLAYER_ACTION_H

#include <cstdint>
#include "common/player_types.h"
#include "game.h"

class PlayerAction
{
public:
    uint16_t player_id;
    PlayerAction(uint16_t player_id) : player_id(player_id) {}
    virtual ~PlayerAction() {}
    virtual void action(Game &game) = 0;
};

/*
        MOVEMENT ACTIONS
*/

class MoveRight : public PlayerAction
{
public:
    MoveRight(uint16_t player_id);
    ~MoveRight();
    void action(Game &game) override;
};

class MoveLeft : public PlayerAction
{
public:
    MoveLeft(uint16_t player_id);
    ~MoveLeft();
    void action(Game &game) override;
};

class MoveUp : public PlayerAction
{
public:
    MoveUp(uint16_t player_id);
    ~MoveUp();
    void action(Game &game) override;
};

class MoveDown : public PlayerAction
{
public:
    MoveDown(uint16_t player_id);
    ~MoveDown();
    void action(Game &game) override;
};

/*
        WEAPON ACTIONS
*/

#endif // !PLAYER_ACTION_H
