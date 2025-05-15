#include "client_action.h"

CreateGame::CreateGame(const std::string& game_name): CreateGameCommon(game_name) {}

CreateGame::~CreateGame() {}

void CreateGame::action(ClientProtocol& protocol) { protocol.send_create_game(this->game_name); }


JoinGame::JoinGame(const std::string& game_name): JoinGame(game_name) {}

JoinGame::~JoinGame() {}

void JoinGame::action(ClientProtocol& protocol) { protocol.send_join_game(this->game_name); }


ListGames::ListGames() {}

ListGames::~ListGames() {}

void ListGames::action(ClientProtocol& protocol) { protocol.send_list_games(); }


Move::Move(MoveType move_type): MoveCommon(move_type) {}

Move::~Move() {}

void Move::action(ClientProtocol& protocol) { protocol.send_move(this->move_type); }