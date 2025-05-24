#include "game.h"

Game::Game(): InterfaceGameManager(), players() {}

Game::~Game() {}

void Game::add_player(player_id_t& player_id) { players.insert({player_id, 0}); }

void Game::process(ClientAction& action) { (void)action; }