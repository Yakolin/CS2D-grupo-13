#include "GameManager.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using std::shared_ptr;
using std::string;

shared_ptr<Player> GameManager::find_player(const player_id_t& player_id) {
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

std::shared_ptr<Player> GameManager::create_player(const player_id_t& id, Team team, Skins& skins) {
    Equipment equipment(id, map_game, map_game, weapon_factory);
    shared_ptr<Player> player = std::make_shared<Player>(id, skins, std::move(equipment), map_game);
    // Equipment le agrega la bomba solo si es TT podemos hacer al arrancar la ronda!
    player = std::make_shared<Player>(id, team, skins, std::move(equipment), map_game);
    return player;
}

void GameManager::add_player(const player_id_t& id, Skins& skins) {
    Team team = ((players.size() + 1) % 2 == 0) ? Team::CT : Team::TT;
    shared_ptr<Player> player = create_player(id, team, skins);
    players.insert(make_pair(id, player));
    map_game.add_player(id, player);  // Player es un ICanInteract
}

void GameManager::reset_players(bool full_reset) {
    for (const auto& player: players) {
        player.second->reset(full_reset);
    }
    // map_game.respawn_players();
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
    game_image.dropped_things = map_game.get_dropped_things_images();
    game_image.bomb = map_game.get_bomb_image();
    return game_image;
}
void GameManager::give_bomb() {
    std::srand(time(NULL));
    std::vector<player_id_t> players_tt;
    for (auto& player: players) {
        if (player.second->get_team() == Team::CT)
            continue;
        players_tt.push_back(player.first);
    }
    if (players_tt.empty())
        throw GameException("Can´t find any TT to give the bomb");

    player_id_t id = players_tt[rand() % players_tt.size()];
    std::shared_ptr<Player> player_selected = find_player(id);
    std::shared_ptr<IDroppable> casted_bomb = bomb;
    player_selected->equip(casted_bomb);
}
void GameManager::start_game() {
    if (players.size() < 1) {
        std::cout << "El juego no tiene suficientes jugadores\n";
        return;
    }
    timer.round_start();
    reset_players(false);
    give_bomb();
    game_started = true;
}
void GameManager::stop_game() {}
bool GameManager::check_round_finished() {
    bool all_ct_dead = true;
    bool all_tt_dead = true;
    for (auto& par: players) {
        if (!par.second->is_dead()) {
            if (par.second->get_team() == Team::CT)
                all_ct_dead = false;
            else
                all_tt_dead = false;
        }
    }
    if (all_ct_dead) {
        game_state.rounds_TT++;
        return true;
    } else if (all_tt_dead) {
        game_state.rounds_CT++;
        return true;
    }
    bool time_end = timer.is_round_over();
    if (time_end && !bomb->is_activate()) {
        game_state.rounds_CT++;
        return true;
    } else if (time_end && bomb->is_activate()) {
        game_state.rounds_TT++;
        return true;
    }
    return false;
}
void GameManager::change_teams() {
    for (auto& player: players) {
        Team team = (player.second->get_team() == Team::CT) ? Team::TT : Team::CT;
        player.second->change_team(team);
    }
}
GameImage GameManager::get_frame() {
    if (round == 10) {
        std::cout << "Juego terminado, rondas: CT: " << game_state.rounds_CT
                  << " TT: " << game_state.rounds_TT << std::endl;
    }
    /*
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
        give_bomb();
    }
    map_game.update_map_state();
    return generate_game_image();
}

void GameManager::remove_player(
        [[maybe_unused]] const player_id_t&  // habria que eliminarlo de todos los lugares
                player_id) {
    map_game.remove_player(player_id);
    // Falta eliminarlo de aca
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
