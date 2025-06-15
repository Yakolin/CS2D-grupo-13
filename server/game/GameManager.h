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
#include "Weapons/WeaponFactory.h"

#include "GameException.h"
#include "Timer.h"
using std::map;
using std::shared_ptr;
using std::string;

class GameManager: public InterfaceGameManager {

    typedef struct GameStats {
        uint8_t rounds_TT;
        uint8_t rounds_CT;
        GameState state;
    } game_stats_t;

private:
    // Configs
    string game_name;
    GameConfig game_config;
    game_stats_t game_stats = {0, 0, GameState::NONE};
    int round = 0;
    bool game_started = false;

    // Players
    map<player_id_t, shared_ptr<Player>> players;
    Timer timer;
    WeaponFactory weapon_factory;
    std::shared_ptr<Bomb> bomb;
    // Map
    Map map_game;

    std::shared_ptr<Player> create_player(const player_id_t& id, Team team, Skins& skins);
    shared_ptr<Player> find_player(const player_id_t& player_id);

    GameImage generate_game_image();
    void give_bomb();
    void reset_round(bool full_reset);
    bool check_round_finished();
    void change_teams();

    // void charge_map(MapName nombre_enum); Esta funcion deberia de mandarle al mapa , crearlo con
    // el path ya buscado desde el yaml
public:
    // Aca el nombre del mapa es inutil, deberia de ser un enum de mapas para saber cuaaal cargar
    explicit GameManager(const string& _game_name, const MapName& map_name):
            game_name(_game_name),
            timer(game_config.get_timer_config()),
            weapon_factory(game_config.get_weapon_config()),
            bomb(std::make_shared<Bomb>(timer)),
            map_game(map_name, bomb) {}
    ~GameManager();
    GameImage get_frame();
    GameInfo get_game_info();
    void start_game();
    void stop_game();
    virtual void process(ClientAction& action) override;
    virtual void add_player(const player_id_t& player_id, Skins& skins) override;
    void remove_player([[maybe_unused]] const player_id_t& player_id);
};

#endif  // GAME_MANAGER_H_
