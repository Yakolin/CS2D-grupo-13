//  "Copyright 2025 Yaco Santamarina"

#include "game.h"
#include <iostream>
void Game::add_player(std::string&&_nick_name, int id) {
    Player::Team team = (players.size() % 2 == 0) ? Player::Team::Terrorist : Player::Team::CounterTerrorist;
    Vector2 position(0,0);
    players.insert(std::make_pair(id, Player(id,std::move(_nick_name), std::move(position), team)));
}

void Game::handle_player_action(int id ,float x, float y){
    //Maybe deberia tirar exception si no esta esa id
    Vector2 position(x,y);
    auto it = players.find(id);
    if (it != players.end()) {
        it->second.move(std::move(position));
    }
}

void Game::start_game(){
    if (players.size() != 2){
        std::cout << "El juego no tiene suficientes jugadores\n";
        return;
    }
    game_started = true;
}
void Game::stop_game() {}

GameImage Game::generate_game_image(){
    if (!game_started) throw std::runtime_error(" Imagen generada cuando el juego nisiquiera esta funcionado");
    GameImage game_image;
    for (auto &pair : players ){
        TypesStates::player_state_t state = pair.second.player_info();
        game_image.add_player_state(std::move(state));
    }
    //Falta la de los objetos sueltos en el mapa, eso seguro se lo pido al mapa
    return game_image;
}

Game::~Game() {
    players.clear();
}
