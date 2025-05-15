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

#include "Map.h"
#include "PlayersTypes.h"
class GameManager {
private:
    std::string game_name;
    std::map<player_id_t, std::shared_ptr<Player>> players;
    int round = 0;
    Map map_game;
    bool game_started = false;
    void handle_player_action(int id, float x, float y);
    GameImage generate_game_image();

public:
    explicit GameManager(const std::string& _game_name, const std::string& map_name):
            game_name(_game_name), map_game(map_name) {}
    ~GameManager();
    void add_player(std::string&& _nick_name, int id);
    GameImage frame(/*vector <PlayerAction>*/);
    void start_game();
    void stop_game();
};

#endif  // GAME_MANAGER_H_
