#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_
//  "Copyright 2025 Yaco Santamarina"
#include <map>
#include <memory>
#include <string>
#include <utility>

#include "../common/game_image.h"
#include "../common/player_command_types.h"
#include "../server/player_action.h"

#include "GameException.h"
#include "InterfaceGameManager.h"
#include "Map.h"
using std::map;
using std::shared_ptr;
using std::string;

class GameManager: public InterfaceGameManager {
private:
    string game_name;
    map<player_id_t, shared_ptr<Player>> players;
    int round = 0;
    Map map_game;
    bool game_started = false;
    shared_ptr<Player> find_player(player_id_t player_id);
    GameImage generate_game_image();

public:
    explicit GameManager(const string& _game_name, const string& map_name):
            game_name(_game_name), map_game(map_name, players) {}
    ~GameManager();
    void add_player(string&& _nick_name, int id);
    GameImage get_frame();
    void start_game();
    void stop_game();

    void move(uint16_t player_id, MoveType move_type) override;
    void shoot(uint16_t player_id, float mouse_x, float mouse_y) override;
    void reload(uint16_t player_id) override;
    void plant_bomb(uint16_t player_id) override;
};

#endif  // GAME_MANAGER_H_
