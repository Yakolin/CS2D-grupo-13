#ifndef GAME_H
#define GAME_H

#include <string>

#include "../common/player_command_types.h"
#include "../common/utility.h"
#include "interfaces/interface_game.h"


class GameManager {
private:
    const std::string& game_name;
    player_id_t player_id;

public:
    GameManager(const std::string& game_name);
    ~GameManager();

    void start_game();
    void stop_game();
    void add_player(player_id_t& new_player);
};

#endif  // !GAME_H
