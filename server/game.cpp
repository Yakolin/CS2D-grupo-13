#include "game.h"

GameManager::GameManager(const std::string& game_name): game_name(game_name), player_id(3) {}
GameManager::~GameManager() {}
void GameManager::start_game() {
    // Implement game start logic here
}
void GameManager::stop_game() {
    // Implement game stop logic here
}

void GameManager::add_player(player_id_t& player_id) { this->player_id = player_id; }
