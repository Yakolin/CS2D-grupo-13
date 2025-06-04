#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_
//  "Copyright 2025 Yaco Santamarina"
#include <map>
#include <memory>
#include <string>
#include <utility>

#include "../../common/game_image.h"
#include "../../common/player_command_types.h"
#include "../interfaces/interface_game.h"
#include "../protocol/client_action.h"

#include "GameException.h"
#include "Map.h"
#include "Player.h"
#include "Timer.h"
using std::map;
using std::shared_ptr;
using std::string;

class GameManager: public InterfaceGameManager {

    typedef struct GameState {
        uint8_t rounds_TT;
        uint8_t rounds_CT;
    } game_state_t;

private:
    string game_name;
    game_state_t game_state = {0, 0};
    map<player_id_t, shared_ptr<Player>> players;
    map<player_id_t, Team> players_team;
    int round = 0;
    Timer timer;
    Map map_game;
    bool game_started = false;
    std::shared_ptr<Player> create_player(const player_id_t& id);
    shared_ptr<Player> find_player(const player_id_t& player_id);
    GameImage generate_game_image();
    void reset_players(bool full_reset);
    bool check_round_finished();
    void change_teams();

    // void charge_map(MapName nombre_enum); Esta funcion deberia de mandarle al mapa , crearlo con
    // el path ya buscado desde el yaml
public:
    // Aca el nombre del mapa es inutil, deberia de ser un enum de mapas para saber cuaaal cargar
    explicit GameManager(const string& _game_name, const string& map_name):
            game_name(_game_name), map_game(map_name) {}
    ~GameManager();
    GameImage get_frame();
    void start_game();
    void stop_game();
    virtual void process(ClientAction& action) override;
    virtual void add_player(const player_id_t& player_id) override;

    /*
        void move(player_id_t player_id, MoveType move_type) override;
        void shoot(player_id_t player_id, coordinate_t mouse_x, coordinate_t mouse_y) override;
        void reload(player_id_t player_id) override;
        void plant_bomb(player_id_t player_id) override;
    */
    void remove_player([[maybe_unused]] const player_id_t&
                               player_id);  // en el caso de que se desconecte hay que implementarlo
};

#endif  // GAME_MANAGER_H_
