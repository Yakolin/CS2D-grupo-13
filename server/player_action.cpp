#include "player_action.h"

/*
        MOVEMENT ACTIONS
*/

MoveDown::MoveDown(std::uint16_t player_id) : PlayerAction(player_id) {}
MoveDown::~MoveDown() {}
void MoveDown::action(Game &game)
{
    game.move_down(this->player_id);
}

MoveLeft::MoveLeft(std::uint16_t player_id) : PlayerAction(player_id) {}
MoveLeft::~MoveLeft() {}
void MoveLeft::action(Game &game)
{
    game.move_left(this->player_id);
}

MoveRight::MoveRight(std::uint16_t player_id) : PlayerAction(player_id) {}
MoveRight::~MoveRight() {}
void MoveRight::action(Game &game)
{
    game.move_right(this->player_id);
}

MoveUp::MoveUp(std::uint16_t player_id) : PlayerAction(player_id) {}
MoveUp::~MoveUp() {}
void MoveUp::action(Game &game)
{
    game.move_up(this->player_id);
}

/*
        WEAPON ACTIONS
*/

BuyWeapon::BuyWeapon(std::uint16_t player_id, WeaponCode weapon_code) : PlayerAction(player_id), weapon_code(weapon_code) {}
BuyWeapon::~BuyWeapon() {}
void BuyWeapon::action(Game &game)
{
    game.buy(this->player_id, this->weapon_code);
}

Reload::Reload(std::uint16_t player_id, WeaponType ammo_type) : PlayerAction(player_id) {}
Reload::~Reload() {}
void Reload::action(Game &game)
{
    game.reload(this->player_id, this->ammo_type);
}
