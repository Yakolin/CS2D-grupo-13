
#include "GameManager.h"

#include <iostream>

#include "../common/game_image.h"

using std::shared_ptr;
using std::string;

void GameManager::add_player(string&& _nick_name, int id) {
    bool is_ct = ((players.size() + 1) % 2 == 0) ? false : true;
    shared_ptr<Player> player;
    Vector2 position(0, 0);
    if (is_ct)
        player = std::make_shared<CounterTerrorist>(id, std::move(_nick_name), std::move(position));
    else
        player = std::make_shared<Terrorist>(id, std::move(_nick_name), std::move(position));
    players.insert(make_pair(id, player));
}

// Decidi que esto se cree cada vez que se pide para evitar datos copiados
GameImage GameManager::generate_game_image() {
    GameImage game_image;
    // Aca posiblemente deba de tambien pedirle al mapa que me de su imagen
    for (const auto& par: players) {
        shared_ptr<Player> player = par.second;
        game_image.players_images.push_back(std::move(player->get_player_image()));
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

// void process_action(unique_ptr<PlayerAction> action) { action.action(this); }


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
    switch (move_type) {
        case MoveType::UP:
            player->move(Vector2(0, 1));
            break;
        case MoveType::DOWN:
            player->move(Vector2(0, -1));
            break;
        case MoveType::RIGHT:
            player->move(Vector2(1, 0));
            break;
        case MoveType::LEFT:
            player->move(Vector2(-1, 0));
            break;
        default:
            throw GameException("MoveType corrupted");
    }
}

void GameManager::shoot(uint16_t player_id, float mouse_x, float mouse_y) {
    shared_ptr<Player> player = find_player(player_id);
    player->fire_weapon_equiped(map_game, Vector2(mouse_x, mouse_y));
}
void GameManager::reload(uint16_t player_id) {
    /*
        shared_ptr<Player> player = find_player(player_id);
        player.reload_current_weapon();
    */
}
void GameManager::plant_bomb(uint16_t player_id) {
    shared_ptr<Player> terro = find_player(player_id);
    if (map_game.bomb_A.is_in(terro->position) || map_game.bomb_B.is_in(terro->position)) {
        std::cout << "El jugador SI esta en una zona de bomba\n";
        // Esto esta mal igual . terro->plant_bomb();
    } else {
        std::cout << "El jugador NO esta en ninguna zona de bomba\n";
    }
}
