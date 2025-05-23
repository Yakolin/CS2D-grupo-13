#ifndef INTERFACE_PLAYER_ACTION_H
#define INTERFACE_PLAYER_ACTION_H

#include "../game/Player.h"

class IActionToPlayer {

public:
    IActionToPlayer() = default;
    virtual ~IActionToPlayer() = default;
    virtual void action_to(Player& player) = 0;
};

#endif  // !INTERFACE_PLAYER_ACTION_H