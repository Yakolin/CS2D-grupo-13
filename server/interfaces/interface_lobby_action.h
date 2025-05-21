#ifndef INTERFACE_LOBBY_ACTION_H
#define INTERFACE_LOBBY_ACTION_H

#include "../../common/socket.h"

#include "interface_games_monitor.h"


class InterfaceLobbyAction {
public:
    InterfaceLobbyAction() = default;
    virtual ~InterfaceLobbyAction() = default;
    virtual void action(Socket& socket, InterfaceGamesMonitor& monitor) = 0;
};

#endif  // !INTERFACE_LOBBY_ACTION_H