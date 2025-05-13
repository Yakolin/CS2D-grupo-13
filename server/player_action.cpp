#include "player_action.h"

/*
        MOVEMENT ACTIONS
*/

MoveDown::MoveDown(uint16_t player_id) : PlayerAction(player_id) {}
MoveDown::~MoveDown() {}
void MoveDown::action(Game &game)
{
    game.move_down(this->player_id);
}

MoveLeft::MoveLeft(uint16_t player_id) : PlayerAction(player_id) {}
MoveLeft::~MoveLeft() {}
void MoveLeft::action(Game &game)
{
    game.move_left(this->player_id);
}

MoveRight::MoveRight(uint16_t player_id) : PlayerAction(player_id) {}
MoveRight::~MoveRight() {}
void MoveRight::action(Game &game)
{
    game.move_right(this->player_id);
}

MoveUp::MoveUp(uint16_t player_id) : PlayerAction(player_id) {}
MoveUp::~MoveUp() {}
void MoveUp::action(Game &game)
{
    game.move_up(this->player_id);
}

/*
        WEAPON ACTIONS
*/

Reload::Reload(uint16_t player_id) : PlayerAction(player_id) {}
Reload::~Reload() {}
void Reload::action(Game &game)
{
    game.reload(this->player_id);
}
