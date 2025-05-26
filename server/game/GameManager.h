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
#include "PlayerType.h"
using std::map;
using std::shared_ptr;
using std::string;

class GameManager: public InterfaceGameManager {

private:
    string game_name;
    map<player_id_t, shared_ptr<Player>> players;
    map<player_id_t, Team> players_team;
    int round = 0;
    Map map_game;
    bool game_started = false;
    shared_ptr<Player> find_player(player_id_t player_id);
    GameImage generate_game_image();
    void reset_players();
    bool check_round_finished();
    void change_teams();

public:
    explicit GameManager(const string& _game_name, const string& map_name):
            game_name(_game_name), map_game(map_name) {}
    ~GameManager();
    GameImage get_frame();
    //void start_game();
    //void stop_game();
    virtual void process(ClientAction& action) override;
    virtual void add_player(player_id_t& player_id) override;
    
    /*
        void move(player_id_t player_id, MoveType move_type) override;
        void shoot(player_id_t player_id, coordinate_t mouse_x, coordinate_t mouse_y) override;
        void reload(player_id_t player_id) override;
        void plant_bomb(player_id_t player_id) override;
    */
};

#endif  // GAME_MANAGER_H_
