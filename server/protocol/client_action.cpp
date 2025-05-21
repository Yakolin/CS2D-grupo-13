#include "client_action.h"

using ServerSpace::BuyAmmo;
using ServerSpace::BuyWeapon;
using ServerSpace::DefuseBomb;
using ServerSpace::Drop;
using ServerSpace::Equip;
using ServerSpace::Move;
using ServerSpace::PlantBomb;
using ServerSpace::Reload;
using ServerSpace::Shoot;


/*
    MOVEMENT ACTIONS
*/

Move::Move(player_id_t player_id, MoveType move_type):
        ClientAction(player_id), InterfacePlayerAction(), MoveCommon(move_type) {}

Move::~Move() {}

void Move::action(InterfaceGame& game) { game.move(this->player_id, this->move_type); }

/*
    WEAPON ACTIONS
*/

BuyWeapon::BuyWeapon(player_id_t player_id, WeaponCode weapon_code):
        ClientAction(player_id), InterfacePlayerAction(), BuyWeaponCommon(weapon_code) {}

BuyWeapon::~BuyWeapon() {}

void BuyWeapon::action(InterfaceGame& game) { game.buy_weapon(this->player_id, this->weapon_code); }


BuyAmmo::BuyAmmo(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count):
        ClientAction(player_id), InterfacePlayerAction(), BuyAmmoCommon(weapon_type, ammo_count) {}

BuyAmmo::~BuyAmmo() {}

void BuyAmmo::action(InterfaceGame& game) {
    game.buy_ammo(this->player_id, this->weapon_type, this->ammo_count);
}


Reload::Reload(player_id_t player_id): ClientAction(player_id), InterfacePlayerAction() {}

Reload::~Reload() {}

void Reload::action(InterfaceGame& game) { game.reload(this->player_id); }


Shoot::Shoot(player_id_t player_id, Position position, ammo_t ammo_count):
        ClientAction(player_id), InterfacePlayerAction(), ShootCommon(position, ammo_count) {}

Shoot::~Shoot() {}

void Shoot::action(InterfaceGame& game) {
    game.shoot(this->player_id, this->position, this->ammo_count);
}

/*
    BOMB ACTIONS
*/

PlantBomb::PlantBomb(player_id_t player_id): ClientAction(player_id), InterfacePlayerAction() {}

PlantBomb::~PlantBomb() {}

void PlantBomb::action(InterfaceGame& game) { game.plant_bomb(this->player_id); }


DefuseBomb::DefuseBomb(player_id_t player_id): ClientAction(player_id), InterfacePlayerAction() {}

DefuseBomb::~DefuseBomb() {}

void DefuseBomb::action(InterfaceGame& game) { game.defuse_bomb(this->player_id); }

/*
GAME ACTIONS
*/

Drop::Drop(player_id_t player_id): ClientAction(player_id), InterfacePlayerAction() {}

Drop::~Drop() {}

void Drop::action(InterfaceGame& game) { game.drop(this->player_id); }


Equip::Equip(player_id_t player_id, EquipType equip_type):
        ClientAction(player_id), InterfacePlayerAction(), EquipCommon(equip_type) {}

Equip::~Equip() {}

void Equip::action(InterfaceGame& game) { game.equip(this->player_id, this->equip_type); }