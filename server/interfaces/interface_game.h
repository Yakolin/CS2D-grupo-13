#ifndef INTERFACE_GAME_H
#define INTERFACE_GAME_H

#include <memory>

#include "../../common/game_image.h"
#include "../../common/player_command_types.h"
#include "../protocol/client_action.h"


class InterfaceGameManager {
public:
    virtual ~InterfaceGameManager() = default;

    virtual void process(ClientAction& action) = 0;
    virtual void add_player(player_id_t& player_id) = 0;
};

#endif  // !INTERFACE_GAME_H
