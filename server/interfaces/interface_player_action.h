#ifndef INTERFACE_PLAYER_ACTION_H
#define INTERFACE_PLAYER_ACTION_H

#include "interface_game.h"

class InterfacePlayerAction {

public:
    InterfacePlayerAction() = default;
    virtual ~InterfacePlayerAction() = default;
    virtual void action(InterfaceGame& game) = 0;
};

#endif  // !INTERFACE_PLAYER_ACTION_H