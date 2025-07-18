#ifndef INTERFACE_GAME_H
#define INTERFACE_GAME_H

#include <memory>

#include "../../common/game_image.h"
#include "../../common/game_info.h"
#include "../../common/player_command_types.h"
#include "../protocol/client_action.h"

#include "interface_player_action.h"


class InterfaceGameManager {
public:
    virtual ~InterfaceGameManager() = default;

    virtual void process(ClientAction& action) = 0;
    virtual void add_player(const player_id_t& player_id, Skins& skins) = 0;
};

#endif  // !INTERFACE_GAME_H
