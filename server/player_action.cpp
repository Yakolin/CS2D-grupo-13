#include "player_action.h"

/*
    MOVEMENT ACTIONS
*/

Move::Move(player_id_t player_id, MoveType move_type) : PlayerAction(player_id), move_type(move_type) {}
Move::~Move() {}
void Move::action(InterfaceGame &game)
{
    game.move(this->player_id, this->move_type);
}

/*
    WEAPON ACTIONS
*/

BuyWeapon::BuyWeapon(player_id_t player_id, WeaponCode weapon_code) : PlayerAction(player_id), weapon_code(weapon_code) {}
BuyWeapon::~BuyWeapon() {}
void BuyWeapon::action(InterfaceGame &game)
{
    game.buy_weapon(this->player_id, this->weapon_code);
}

BuyAmmo::BuyAmmo(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count) : PlayerAction(player_id), weapon_type(weapon_type), ammo_count(ammo_count) {}
BuyAmmo::~BuyAmmo() {}
void BuyAmmo::action(InterfaceGame &game)
{
    game.buy_ammo(this->player_id, this->weapon_type, this->ammo_count);
}

Reload::Reload(player_id_t player_id, WeaponType weapon_type) : PlayerAction(player_id), weapon_type(weapon_type) {}
Reload::~Reload() {}
void Reload::action(InterfaceGame &game)
{
    game.reload(this->player_id, this->weapon_type);
}

Shoot::Shoot(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count) : PlayerAction(player_id), weapon_type(weapon_type), ammo_count(ammo_count) {}
Shoot::~Shoot() {}
void Shoot::action(InterfaceGame &game)
{
    game.shoot(this->player_id, this->weapon_type, this->ammo_count);
}

DropWeapon::DropWeapon(player_id_t player_id, WeaponType weapon_type) : PlayerAction(player_id), weapon_type(weapon_type) {}
DropWeapon::~DropWeapon() {}
void DropWeapon::action(InterfaceGame &game)
{
    game.drop_weapon(this->player_id);
}

/*
    BOMB ACTIONS
*/

PlantBomb::PlantBomb(player_id_t player_id) : PlayerAction(player_id) {}
PlantBomb::~PlantBomb() {}
void PlantBomb::action(InterfaceGame &game)
{
    game.plant_bomb(this->player_id);
}

DropBomb::DropBomb(player_id_t player_id) : PlayerAction(player_id) {}
DropBomb::~DropBomb() {}
void DropBomb::action(InterfaceGame &game)
{
    game.drop_bomb(this->player_id);
}

DefuseBomb::DefuseBomb(player_id_t player_id) : PlayerAction(player_id) {}
DefuseBomb::~DefuseBomb() {}
void DefuseBomb::action(InterfaceGame &game)
{
    game.defuse_bomb(this->player_id);
}
