#ifndef GAME_H
#define GAME_H

#include <map>

#include "../../common/player_command_types.h"
#include "../interfaces/interface_game.h"

#include "client_action.h"


class Game: public InterfaceGameManager {
private:
    std::map<player_id_t, player_id_t> players;

public:
    Game();
    ~Game();
    void add_player(player_id_t& player_id) override;
    void process(ClientAction& action) override;
};

#endif  // !GAME_H