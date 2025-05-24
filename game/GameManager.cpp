#include "GameManager.h"

#include <iostream>

#include "../common/game_image.h"

using std::shared_ptr;
using std::string;

shared_ptr<Player> GameManager::find_player(player_id_t player_id) {
    auto it = players.find(player_id);
    if (it != players.end())
        return it->second;
    else
        throw GameException("Player not found in the map structure");
}
void GameManager::add_player(string&& _nick_name, player_id_t id) {
    Team team = ((players.size() + 1) % 2 == 0) ? Team::CT : Team::TT;
    shared_ptr<Player> player;
    if (team == Team::CT)
        player = std::make_shared<CounterTerrorist>(id, std::move(_nick_name));
    else
        player = std::make_shared<Terrorist>(id, std::move(_nick_name));
    players.insert(make_pair(id, player));
    players_team.insert(std::make_pair(id, team));
    map_game.add_player(id);
}
void GameManager::reset_players() {
    for (const auto& player: players) {
        player.second->reset();
    }
    map_game.respawn_players(players_team);
}
// Decidi que esto se cree cada vez que se pide para evitar datos copiados
GameImage GameManager::generate_game_image() {
    GameImage game_image;
    // Aca posiblemente deba de tambien pedirle al mapa que me de su imagen
    for (const auto& par: players) {
        shared_ptr<Player> player = par.second;
        Position player_position = map_game.get_position(par.first);
        game_image.players_images.push_back(std::move(player->get_player_image(player_position)));
    }
    return game_image;
}

void GameManager::start_game() {
    if (players.size() != 2) {
        std::cout << "El juego no tiene suficientes jugadores\n";
        return;
    }
    reset_players();
    game_started = true;
}
void GameManager::stop_game() {}
bool GameManager::check_round_finished() { return false; }
void GameManager::change_teams() {
    for (const auto& player: players_team) {
        std::string nick_name = players[player.first]->get_nick_name();
        if (player.second == Team::CT) {
            players_team[player.first] = Team::TT;
            players[player.first] = std::make_shared<Terrorist>(player.first, std::move(nick_name));
        } else {
            players_team[player.first] = Team::CT;
            players[player.first] = std::make_shared<Terrorist>(player.first, std::move(nick_name));
        }
    }
}
GameImage GameManager::get_frame() {
    if (!game_started)
        throw GameException("The game isn´t start yet to take a frame");
    /*
        1. Actualizar las cosas en el Mapa , como movimiento de las balas , armas q caen
        2. Chekear colisiones que no sean propias del jugador (colisiones de bala por ejemplo)
        3. Manejar esas colisiones como balas chocando, etc
    */
    if (check_round_finished()) {
        std::cout << "Ronda terminada\n";
        round++;
        reset_players();
    }
    if (round == 5) {
        std::cout << "A cambiar de equipos" << std::endl;
        change_teams();
    }
    map_game.update_map_state();
    return generate_game_image();
}
GameManager::~GameManager() { players.clear(); }

/* InterfaceGameManager */

void GameManager::move(player_id_t player_id, MoveType move_type) {
    switch (move_type) {
        case MoveType::UP:
            map_game.move_player(player_id, Position(0, 1));
            break;
        case MoveType::DOWN:
            map_game.move_player(player_id, Position(0, -1));
            break;
        case MoveType::RIGHT:
            map_game.move_player(player_id, Position(1, 0));
            break;
        case MoveType::LEFT:
            map_game.move_player(player_id, Position(-1, 0));
            break;
        default:
            throw GameException("MoveType corrupted");
    }
}

void GameManager::shoot(player_id_t player_id, coordinate_t mouse_x, coordinate_t mouse_y) {
    shared_ptr<Player> player = find_player(player_id);
    Position position = map_game.get_position(player_id);
    Position direction = position - Position(mouse_x, mouse_y);
    // direction.normalize(); Aca entra el tema de como calcular el movimiento de las balas
    player->fire_weapon_equiped(map_game, position, direction);
}
void GameManager::reload(player_id_t player_id) {
    /*
        shared_ptr<Player> player = find_player(player_id);
        player.reload_current_weapon();
    */
}
void GameManager::plant_bomb(player_id_t player_id) {
    /* shared_ptr<Player> terro = find_player(player_id);
    Position player_position = map_game.get_position(player_id);

    if (map_game.bomb_A.is_in(player_position) || map_game.bomb_B.is_in(player_position)) {
        std::cout << "El jugador SI esta en una zona de bomba\n";
    } else {
        std::cout << "El jugador NO esta en ninguna zona de bomba\n";
    }
    */
}
