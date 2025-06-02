#include "GameManager.h"

#include <iostream>

using std::shared_ptr;
using std::string;

shared_ptr<Player> GameManager::find_player(player_id_t player_id) {
    auto it = players.find(player_id);
    if (it != players.end())
        return it->second;
    else
        throw GameException("Player not found in the map structure");
}

void GameManager::process(ClientAction& action) {
    if (timer.is_time_buy()) {  // Aca hay que mejorar la logica de compra y demas
        return;
    }
    player_id_t player_id = action.get_player_id();
    shared_ptr<Player> player = find_player(player_id);
    action.action_to(*player);
}

std::shared_ptr<Player> GameManager::create_player(player_id_t id) {
    Equipement equipement;
    shared_ptr<Player> player;
    // Equipement le agrega la bomba solo si es TT podemos hacer al arrancar la ronda!
    player = std::make_shared<Player>(id, std::move(equipement), map_game, map_game);
    return player;
}
void GameManager::add_player(player_id_t& id) {
    Team team = ((players.size() + 1) % 2 == 0) ? Team::CT : Team::TT;
    shared_ptr<Player> player = create_player(id);
    players.insert(make_pair(id, player));
    std::cout << "Añado un jugador a la partida" << id << std::endl;
    players_team.insert(std::make_pair(id, team));
    map_game.add_player(id, player);  // Player es un ICanInteract
}
void GameManager::reset_players(bool full_reset) {
    for (const auto& player: players) {
        player.second->reset(full_reset);
    }
    map_game.respawn_players(players_team);
}
// Decidi que esto se cree cada vez que se pide para evitar datos copiados
GameImage GameManager::generate_game_image() {
    GameImage game_image;
    game_image.round = round;
    game_image.time = timer.get_time_round();
    // Aca posiblemente deba de tambien pedirle al mapa que me de su imagen
    for (const auto& par: players) {
        shared_ptr<Player> player = par.second;
        Position player_position = map_game.get_position(par.first);
        game_image.players_images.push_back(std::move(player->get_player_image(player_position)));
    }
    return game_image;
}
void GameManager::start_game() {
    if (players.size() < 1) {
        std::cout << "El juego no tiene suficientes jugadores\n";
        return;
    }
    timer.round_start();
    reset_players(true);
    game_started = true;
}
void GameManager::stop_game() {}
bool GameManager::check_round_finished() { return timer.is_round_over(); }  // Faltan cosas aca
void GameManager::change_teams() {
    for (const auto& player: players_team) {
        players_team[player.first] = (player.second == Team::CT) ? Team::TT : Team::CT;
    }
}
GameImage GameManager::get_frame() {
    /*
    if (!game_started)
        throw GameException("The game isn´t start yet to take a frame");
        1. Actualizar las cosas en el Mapa , como movimiento de las balas , armas q caen
        2. Chekear colisiones que no sean propias del jugador (colisiones de bala por ejemplo)
        3. Manejar esas colisiones como balas chocando, etc
    */
    if (check_round_finished()) {
        round++;
        bool full_reset = false;
        std::cout << "Ronda terminada\n";
        if (round == 5) {
            // Aca si deberia de resetearse de forma forzada
            std::cout << "A cambiar de equipos" << std::endl;
            change_teams();
            full_reset = true;
        }
        timer.round_start();
        reset_players(full_reset);
        // give_bomb() , deberia estar aca posiblemente
    }
    map_game.update_map_state();
    return generate_game_image();
}
GameManager::~GameManager() { players.clear(); }

/*
void GameManager::reload(player_id_t player_id) {
        shared_ptr<Player> player = find_player(player_id);
        player.reload_current_weapon();
}
void GameManager::plant_bomb(player_id_t player_id) {
    shared_ptr<Player> terro = find_player(player_id);
    Vector2 player_position = map_game.get_position(player_id);

    if (map_game.bomb_A.is_in(player_position) || map_game.bomb_B.is_in(player_position)) {
}
*/
