#include "player_action.h"

using Server::BuyAmmo;
using Server::BuyWeapon;
using Server::CreateGame;
using Server::DefuseBomb;
using Server::DropBomb;
using Server::DropWeapon;
using Server::JoinGame;
using Server::ListGames;
using Server::Move;
using Server::PlantBomb;
using Server::Reload;
using Server::Shoot;

/*
    CREATE GAME
*/

CreateGame::CreateGame(player_id_t player_id, const std::string& game_name):
        ClientAction(player_id), InterfaceLobbyAction(), CreateGameCommon(game_name) {}

CreateGame::~CreateGame() {}

void CreateGame::action(InterfaceGamesMonitor& monitor) {
    monitor.create_game(this->player_id, this->game_name);
}
/*
        PLAYER ACTIONS
*/
/*
    JOIN GAME
*/

JoinGame::JoinGame(player_id_t player_id, const std::string& game_name):
        ClientAction(player_id), InterfaceLobbyAction(), JoinGameCommon(game_name) {}

JoinGame::~JoinGame() {}

void JoinGame::action(InterfaceGamesMonitor& monitor) {
    monitor.join_game(this->player_id, this->game_name);
}

/*
    LIST GAMES
*/

ListGames::ListGames(player_id_t player_id): ClientAction(player_id), InterfaceLobbyAction() {}

ListGames::~ListGames() {}

void ListGames::action(InterfaceGamesMonitor& monitor) { monitor.list_games(); }

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


Reload::Reload(player_id_t player_id, WeaponType weapon_type):
        ClientAction(player_id), InterfacePlayerAction(), ReloadCommon(weapon_type) {}

Reload::~Reload() {}

void Reload::action(InterfaceGame& game) { game.reload(this->player_id, this->weapon_type); }


Shoot::Shoot(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count):
        ClientAction(player_id), InterfacePlayerAction(), ShootCommon(weapon_type, ammo_count) {}

Shoot::~Shoot() {}

void Shoot::action(InterfaceGame& game) {
    game.shoot(this->player_id, this->weapon_type, this->ammo_count);
}


DropWeapon::DropWeapon(player_id_t player_id, WeaponType weapon_type):
        ClientAction(player_id), InterfacePlayerAction(), DropWeaponCommon(weapon_type) {}

DropWeapon::~DropWeapon() {}

void DropWeapon::action(InterfaceGame& game) { game.drop_weapon(this->player_id); }

/*
    BOMB ACTIONS
*/

PlantBomb::PlantBomb(player_id_t player_id): ClientAction(player_id), InterfacePlayerAction() {}

PlantBomb::~PlantBomb() {}

void PlantBomb::action(InterfaceGame& game) { game.plant_bomb(this->player_id); }


DropBomb::DropBomb(player_id_t player_id): ClientAction(player_id), InterfacePlayerAction() {}

DropBomb::~DropBomb() {}

void DropBomb::action(InterfaceGame& game) { game.drop_bomb(this->player_id); }


DefuseBomb::DefuseBomb(player_id_t player_id): ClientAction(player_id), InterfacePlayerAction() {}

DefuseBomb::~DefuseBomb() {}

void DefuseBomb::action(InterfaceGame& game) { game.defuse_bomb(this->player_id); }
