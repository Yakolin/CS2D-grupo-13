#include "client_action.h"

using Client::BuyAmmo;
using Client::BuyWeapon;
using Client::CreateGame;
using Client::DefuseBomb;
using Client::Drop;
using Client::Equip;
using Client::JoinGame;
using Client::ListGames;
using Client::Move;
using Client::PlantBomb;
using Client::Reload;
using Client::Shoot;

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