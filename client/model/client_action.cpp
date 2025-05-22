#include "client_action.h"

using ClientSpace::BuyAmmo;
using ClientSpace::BuyWeapon;
using ClientSpace::CreateGame;
using ClientSpace::DefuseBomb;
using ClientSpace::Drop;
using ClientSpace::Equip;
using ClientSpace::JoinGame;
using ClientSpace::ListGames;
using ClientSpace::Move;
using ClientSpace::PlantBomb;
using ClientSpace::Reload;
using ClientSpace::Shoot;

CreateGame::CreateGame(const std::string& game_name):
        CreateGameCommon(game_name), InterfaceClientAction() {}

CreateGame::~CreateGame() {}

void CreateGame::action(ClientProtocol& protocol) { protocol.send_create_game(this->game_name); }


JoinGame::JoinGame(const std::string& game_name):
        JoinGameCommon(game_name), InterfaceClientAction() {}

JoinGame::~JoinGame() {}

void JoinGame::action(ClientProtocol& protocol) { protocol.send_join_game(this->game_name); }


ListGames::ListGames() {}

ListGames::~ListGames() {}

void ListGames::action(ClientProtocol& protocol) { protocol.send_list_games(); }


Move::Move(MoveType move_type): MoveCommon(move_type), InterfaceClientAction() {}

Move::~Move() {}

void Move::action(ClientProtocol& protocol) { protocol.send_move(this->move_type); }