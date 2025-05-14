//  "Copyright 2025 Yaco Santamarina"

#include "GameManager.h"
#include <iostream>
void GameManager::add_player(std::string&&_nick_name, int id) {
    Player::Team team = (players.size() % 2 == 0) ? Player::Team::Terrorist : Player::Team::CounterTerrorist;
    Vector2 position(0,0);
    players.insert(std::make_pair(id, Player(id,std::move(_nick_name), std::move(position), team)));
}

void GameManager::handle_player_action(int id ,float x, float y){
    //Maybe deberia tirar exception si no esta esa id
    auto it = players.find(id);
    if (it != players.end()) {
        it->second.move(std::move(Vector2(x,y)));
    }
}

void GameManager::start_game(){
    if (players.size() != 2){
        std::cout << "El juego no tiene suficientes jugadores\n";
        return;
    }
    game_started = true;
}
void GameManager::stop_game() {}

GameImage GameManager::generate_game_image(){
    GameImage game_image;
    for (auto &pair : players ){
        TypesStates::player_state_t state = pair.second.player_info();
        game_image.add_player_state(std::move(state));
    }
    //Falta la de los objetos sueltos en el mapa, eso seguro se lo pido al mapa
    return game_image;
}

GameImage GameManager::frame(/*vector <PlayerAction>*/){
    if (!game_started) throw std::runtime_error(" Imagen generada cuando el juego nisiquiera esta funcionado");
    /*
        1. Procesar Todas las PlayerActions , como disparar, moverse, etc.
        2. Actualizar las cosas en el Mapa , como movimiento de las balas , armas q caen
        3. Chekear colisiones
        4. Manejar esas colisiones como balas chocando
    */
    handle_player_action(1,1,1);
    return generate_game_image();
}

GameManager::~GameManager() {
    players.clear();
}
