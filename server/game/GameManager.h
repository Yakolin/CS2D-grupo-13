#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_
//  "Copyright 2025 Yaco Santamarina"
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../common/game_image.h"
#include "../../common/player_command_types.h"
#include "../interfaces/interface_game.h"
#include "../protocol/client_action.h"
#include "Config/GameConfig.h"
#include "Map/Map.h"
#include "Player/Player.h"
#include "Sounds/SoundManager.h"
#include "Weapons/WeaponFactory.h"

#include "GameException.h"
#include "Timer.h"
using std::map;
using std::shared_ptr;
using std::string;

class GameManager: public InterfaceGameManager {

    typedef struct GameStats {
        uint8_t players_tt;
        uint8_t players_ct;
        uint8_t rounds_TT;
        uint8_t rounds_CT;
        GameState state;
    } game_stats_t;

private:
    // Configs
    string game_name;
    GameConfig game_config;
    game_stats_t game_stats = {0, 0, 0, 0, GameState::NONE};
    int round = 1;
    bool game_started = false;

    // Players
    map<player_id_t, shared_ptr<Player>> players;
    Timer timer;
    WeaponFactory weapon_factory;
    std::shared_ptr<Bomb> bomb;
    // Map
    Map map_game;
    // Sound
    SoundManager sound_manager;

    std::shared_ptr<Player> create_player(const player_id_t& id, Team team, Skins& skins);
    shared_ptr<Player> find_player(const player_id_t& player_id);

    GameImage generate_game_image();
    void give_bomb();
    void give_money_team(Team team);
    void reset_round(bool full_reset);
    bool check_round_finished();
    void update_teams_count(Team from);
    void handle_empty_team();
    bool enough_players_teams();
    void change_teams();

public:
    explicit GameManager(const string& _game_name, const MapName& map_name):
            game_name(_game_name),
            timer(game_config.get_timer_config()),
            weapon_factory(game_config.get_weapon_config()),
            bomb(std::make_shared<Bomb>(timer)),
            map_game(map_name, bomb, sound_manager) {}
    ~GameManager();
    GameImage get_frame();
    GameInfo get_game_info();
    void start_game();
    bool has_players();
    bool has_ended();
    void stop_game();
    virtual void process(ClientAction& action) override;
    virtual void add_player(const player_id_t& player_id, Skins& skins) override;
    void remove_player([[maybe_unused]] const player_id_t& player_id);
};

#endif  // GAME_MANAGER_H_
