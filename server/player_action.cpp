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
    game.buy_weapon(this->player_id, this->weapon_code);
}

BuyAmmo::BuyAmmo(std::uint16_t player_id, WeaponType weapon_type, ammo_t ammo_count) : PlayerAction(player_id), weapon_type(weapon_type), ammo_count(ammo_count) {}
BuyAmmo::~BuyAmmo() {}
void BuyAmmo::action(Game &game)
{
    game.buy_ammo(this->player_id, this->weapon_type, this->ammo_count);
}

Reload::Reload(std::uint16_t player_id, WeaponType ammo_type) : PlayerAction(player_id) {}
Reload::~Reload() {}
void Reload::action(Game &game)
{
    game.reload(this->player_id, this->ammo_type);
}

Shoot::Shoot(std::uint16_t player_id, WeaponType weapon_type, ammo_t ammo_count) : PlayerAction(player_id), weapon_type(weapon_type), ammo_count(ammo_count) {}
Shoot::~Shoot() {}
void Shoot::action(Game &game)
{
    game.shoot(this->player_id, this->weapon_type, this->ammo_count);
}

DropWeapon::DropWeapon(std::uint16_t player_id, WeaponType weapon_type) : PlayerAction(player_id), weapon_type(weapon_type) {}
DropWeapon::~DropWeapon() {}
void DropWeapon::action(Game &game)
{
    game.drop_weapon(this->player_id);
}

/*
        BOMB ACTIONS
*/

PlantBomb::PlantBomb(std::uint16_t player_id) : PlayerAction(player_id) {}
PlantBomb::~PlantBomb() {}
void PlantBomb::action(Game &game)
{
    game.plant_bomb(this->player_id);
}

DropBomb::DropBomb(std::uint16_t player_id) : PlayerAction(player_id) {}
DropBomb::~DropBomb() {}
void DropBomb::action(Game &game)
{
    game.drop_bomb(this->player_id);
}

DefuseBomb::DefuseBomb(std::uint16_t player_id) : PlayerAction(player_id) {}
DefuseBomb::~DefuseBomb() {}
void DefuseBomb::action(Game &game)
{
    game.defuse_bomb(this->player_id);
}
