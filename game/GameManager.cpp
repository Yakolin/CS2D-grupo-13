
#include "GameManager.h"

#include <iostream>

#include "../common/game_image.h"
void GameManager::add_player(std::string&& _nick_name, int id) {
    bool is_ct = (players.size() % 2 == 0) ? false : true;
    std::shared_ptr<Player> player;
    Vector2 position(0, 0);
    if (is_ct)
        player = std::make_shared<CounterTerrorist>(id, std::move(_nick_name), std::move(position));
    else
        player = std::make_shared<CounterTerrorist>(id, std::move(_nick_name), std::move(position));
    players.insert(std::make_pair(id, player));
}
void GameManager::start_game() {
    if (players.size() != 2) {
        std::cout << "El juego no tiene suficientes jugadores\n";
        return;
    }
    game_started = true;
}
void GameManager::stop_game() {}
/*
GameImage GameManager::frame() {
    // if (!game_started) throw new GameException("E");

        1. Actualizar las cosas en el Mapa , como movimiento de las balas , armas q caen
        2. Chekear colisiones
        3. Manejar esas colisiones como balas chocando, etc

    handle_player_action(1, 1, 1);
    return generate_game_image();
}
// void process_action(std::unique_ptr<PlayerAction> action) { action.action(this); }
*/
GameManager::~GameManager() { players.clear(); }
