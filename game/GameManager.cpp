
#include "GameManager.h"

#include <iostream>

#include "../common/game_image.h"

using std::shared_ptr;
using std::string;

void GameManager::add_player(string&& _nick_name, player_id_t id) {
    bool is_ct = ((players.size() + 1) % 2 == 0) ? false : true;
    shared_ptr<Player> player;
    if (is_ct)
        player = std::make_shared<CounterTerrorist>(id, std::move(_nick_name));
    else
        player = std::make_shared<Terrorist>(id, std::move(_nick_name));
    players.insert(make_pair(id, player));
    map_game.add_player(id); //Aca quizas deberia de decirle QUE tipo es, de alguna forma debe saberlo el map
}

// Decidi que esto se cree cada vez que se pide para evitar datos copiados
GameImage GameManager::generate_game_image() {
    GameImage game_image;
    // Aca posiblemente deba de tambien pedirle al mapa que me de su imagen
    for (const auto& par: players) {
        shared_ptr<Player> player = par.second;
        Vector2 player_position = map_game.player_position(par.first);
        game_image.players_images.push_back(std::move(player->get_player_image(player_position)));
    }
    return game_image;
}

void GameManager::start_game() {
    if (players.size() != 2) {
        std::cout << "El juego no tiene suficientes jugadores\n";
        return;
    }
    game_started = true;
}
void GameManager::stop_game() {}

GameImage GameManager::get_frame() {
    if (!game_started)
        throw GameException("The game isn´t start yet to take a frame");
    /*
        1. Actualizar las cosas en el Mapa , como movimiento de las balas , armas q caen
        2. Chekear colisiones que no sean propias del jugador (colisiones de bala por ejemplo)
        3. Manejar esas colisiones como balas chocando, etc
    */
    map_game.update_map_state();

    return generate_game_image();
}
GameManager::~GameManager() { players.clear(); }

shared_ptr<Player> GameManager::find_player(player_id_t player_id) {
    auto it = players.find(player_id);
    if (it != players.end())
        return it->second;
    else
        throw GameException("Player not found in the map structure");
}

/* InterfaceGameManager */

void GameManager::move(uint16_t player_id, MoveType move_type) {
    shared_ptr<Player> player = find_player(player_id);
    // Esto no va mas, es necesario que el MAPA los mueva en su contexto
    switch (move_type) {
        case MoveType::UP:
            map_game.move_player(player_id, Vector2(0,1));
            break;
        case MoveType::DOWN:
            map_game.move_player(player_id, Vector2(0,-1));
            break;
        case MoveType::RIGHT:
            map_game.move_player(player_id, Vector2(1,0));
            break;
        case MoveType::LEFT:
            map_game.move_player(player_id, Vector2(-1,0));
            break;
        default:
            throw GameException("MoveType corrupted");
    }
}

void GameManager::shoot(uint16_t player_id, coordinate_t mouse_x, coordinate_t mouse_y) {
    shared_ptr<Player> player = find_player(player_id);
    //Aca falta laburar el tema este de que en realidad el mapa nos tiene que decir la posicion actual del player en el mapa
    Vector2 a(0,0);
    Vector2 direction = a - Vector2(mouse_x, mouse_y);
    player->fire_weapon_equiped(map_game, a, direction);
}
void GameManager::reload(uint16_t player_id) {
    /*
        shared_ptr<Player> player = find_player(player_id);
        player.reload_current_weapon();
    */
}
void GameManager::plant_bomb(uint16_t player_id) {
    shared_ptr<Player> terro = find_player(player_id);
    //Aca igual,  deberia de encargarse el MAPA!
    Vector2 player_position = map_game.player_position(player_id);
    if (map_game.bomb_A.is_in(player_position) || map_game.bomb_B.is_in(player_position)) {
        std::cout << "El jugador SI esta en una zona de bomba\n";
        // Esto esta mal igual . terro->plant_bomb();
    } else {
        std::cout << "El jugador NO esta en ninguna zona de bomba\n";
    }
}
