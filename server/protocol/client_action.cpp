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
        ClientAction(player_id), IActionToPlayer(), MoveCommon(move_type) {}

Move::~Move() {}

void Move::action(InterfaceGameManager& game) { game.move(this->player_id, this->move_type); }

/*
    WEAPON ACTIONS
*/

BuyWeapon::BuyWeapon(player_id_t player_id, WeaponCode weapon_code):
        ClientAction(player_id), IActionToPlayer(), BuyWeaponCommon(weapon_code) {}

BuyWeapon::~BuyWeapon() {}

void BuyWeapon::action(InterfaceGameManager& game) {
    game.buy_weapon(this->player_id, this->weapon_code);
}


BuyAmmo::BuyAmmo(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count):
        ClientAction(player_id), IActionToPlayer(), BuyAmmoCommon(weapon_type, ammo_count) {}

BuyAmmo::~BuyAmmo() {}

void BuyAmmo::action(InterfaceGameManager& game) {
    game.buy_ammo(this->player_id, this->weapon_type, this->ammo_count);
}


Reload::Reload(player_id_t player_id): ClientAction(player_id), IActionToPlayer() {}

Reload::~Reload() {}

void Reload::action(InterfaceGameManager& game) { game.reload(this->player_id); }


Shoot::Shoot(player_id_t player_id, Position position, ammo_t ammo_count):
        ClientAction(player_id), IActionToPlayer(), ShootCommon(position, ammo_count) {}

Shoot::~Shoot() {}

void Shoot::action(InterfaceGameManager& game) {
    game.shoot(this->player_id, this->position, this->ammo_count);
}

/*
    BOMB ACTIONS
*/

PlantBomb::PlantBomb(player_id_t player_id): ClientAction(player_id), IActionToPlayer() {}

PlantBomb::~PlantBomb() {}

void PlantBomb::action(InterfaceGameManager& game) { game.plant_bomb(this->player_id); }


DefuseBomb::DefuseBomb(player_id_t player_id): ClientAction(player_id), IActionToPlayer() {}

DefuseBomb::~DefuseBomb() {}

void DefuseBomb::action(InterfaceGameManager& game) { game.defuse_bomb(this->player_id); }

/*
GAME ACTIONS
*/

Drop::Drop(player_id_t player_id): ClientAction(player_id), IActionToPlayer() {}

Drop::~Drop() {}

void Drop::action(InterfaceGameManager& game) { game.drop(this->player_id); }


Equip::Equip(player_id_t player_id, EquipType equip_type):
        ClientAction(player_id), IActionToPlayer(), EquipCommon(equip_type) {}

Equip::~Equip() {}

void Equip::action(InterfaceGameManager& game) { game.equip(this->player_id, this->equip_type); }