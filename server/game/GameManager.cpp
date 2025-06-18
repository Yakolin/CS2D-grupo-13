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
    if (timer.is_time_to_buy()) {
        const ServerSpace::BuyWeapon* action_casted =
                dynamic_cast<ServerSpace::BuyWeapon*>(&action);
        if (!action_casted)
            return;
    }
    player_id_t player_id = action.get_player_id();
    shared_ptr<Player> player = find_player(player_id);
    if (player->is_dead())
        return;
    action.action_to(*player);
}

std::shared_ptr<Player> GameManager::create_player(const player_id_t& id, Team team, Skins& skins) {
    Equipment equipment(id, map_game, map_game, weapon_factory);
    shared_ptr<Player> player = std::make_shared<Player>(
            id, team, skins, game_config.get_player_config(), std::move(equipment), map_game);
    return player;
}

void GameManager::add_player(const player_id_t& id, Skins& skins) {
    Team team = ((players.size() + 1) % 2 == 0) ? Team::CT : Team::TT;
    shared_ptr<Player> player = create_player(id, team, skins);
    players.insert(make_pair(id, player));
    map_game.add_player(id, player);  // Player es un ICanInteract
}

void GameManager::reset_round(bool full_reset) {
    for (const auto& player: players) player.second->reset(full_reset);
    map_game.respawn_players();
    std::vector<std::shared_ptr<IInteractuable>> weapons;
    for (int i = 0; i < game_config.get_max_dropped_weapons(); i++) {
        std::shared_ptr<IInteractuable> weapon =
                weapon_factory.create_random_weapon(game_config.get_dropped_weapons());
        weapons.push_back(weapon);
    }
    map_game.spawn_random_weapons(weapons);
    give_bomb();
}
// Decidi que esto se cree cada vez que se pide para evitar datos copiados
GameImage GameManager::generate_game_image() {
    GameImage game_image;
    for (const auto& par: players) {
        shared_ptr<Player> player = par.second;
        Position player_position = map_game.get_position(par.first);
        game_image.players_images.push_back(std::move(player->get_player_image(player_position)));
    }
    game_image.bullets_in_air = map_game.get_bullets_in_air();
    game_image.dropped_things = map_game.get_dropped_things_images();
    game_image.bomb = map_game.get_bomb_image();
    GameStateImage game_state_image(game_stats.state,
                                    static_cast<round_time_t>(timer.get_time_round()),
                                    static_cast<round_t>(round));
    game_image.game_state = game_state_image;
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
    std::shared_ptr<IInteractuable> casted_bomb = bomb;
    player_selected->equip(casted_bomb);
}
void GameManager::start_game() {
    if (players.size() < 1) {
        std::cout << "El juego no tiene suficientes jugadores\n";
        return;
    }
    WeaponConfig::get_instance().load(WEAPON_CONFIG_PATH);
    timer.round_start();
    reset_round(false);
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
        game_stats.rounds_TT++;
        return true;
    } else if (all_tt_dead) {
        game_stats.rounds_CT++;
        return true;
    }
    bool time_end = timer.is_round_over();
    if (bomb->is_defused() || (time_end && !bomb->is_activate())) {
        game_stats.rounds_CT++;
        game_stats.state = GameState::CT_WIN_ROUND;
        return true;
    } else if (time_end && !bomb->is_defused()) {
        game_stats.rounds_TT++;
        game_stats.state = GameState::TT_WIN_ROUND;
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
    if (round == game_config.get_max_rounds()) {
        game_stats.state = (game_stats.rounds_TT > game_stats.rounds_CT) ? GameState::TT_WIN_GAME :
                                                                           GameState::CT_WIN_GAME;
        return generate_game_image();
    }
    if (timer.is_time_to_buy()) {
        game_stats.state = GameState::TIME_TO_BUY;
    } else if (timer.get_state() != TimerState::ENDING_TIME) {
        game_stats.state = GameState::ROUND_STARTED;
        bool round_finished = check_round_finished();
        if (round_finished)
            timer.round_end();
    }
    // Si ya termino el tiempo ending
    if (timer.get_state() == TimerState::ENDING_TIME && timer.get_time_round() == 0) {
        round++;
        bool full_reset = false;
        // Quiza no deberia ser asi, es decir, / 2 ??
        if (round == game_config.get_max_rounds() / 2) {
            change_teams();
            full_reset = true;
        }
        timer.round_start();
        reset_round(full_reset);
    }
    map_game.update_map_state();
    return generate_game_image();
}
GameInfo GameManager::get_game_info() {
    MapInfo map_info = map_game.get_map_info();
    std::vector<WeaponInfo> purchasables = game_config.get_info_weapons();
    return GameInfo(map_info, purchasables);
}
void GameManager::remove_player(
        [[maybe_unused]] const player_id_t&  // habria que eliminarlo de todos los lugares
                player_id) {
    map_game.remove_player(player_id);
    std::shared_ptr<Player> player = find_player(player_id);
    // Esto es para matarlo antes de que se vaya, evitamos tener que hacer mas metodos sobre la
    // bomba y demas.
    player->damage(200);  // Quiza un metodo kill sea mejor que esto...
    players.erase(player_id);
}

GameManager::~GameManager() { players.clear(); }
