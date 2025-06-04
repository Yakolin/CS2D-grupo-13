#ifndef FUNCTOR_PARSE_CLIENT_ACTION_H
#define FUNCTOR_PARSE_CLIENT_ACTION_H

#include <memory>

#include "../../common/client_common_action.h"
#include "../../common/game_info.h"
#include "../../common/lobby_types.h"
#include "../interfaces/interface_games_monitor.h"

#include "client_action.h"
#include "games_monitor.h"
#include "protocol.h"


class ParseAction {
protected:
    player_id_t& player_id;
    ServerProtocol& protocol;

public:
    ParseAction(player_id_t& player_id, ServerProtocol& protocol):
            player_id(player_id), protocol(protocol) {}
    virtual ~ParseAction() = default;

    virtual void run() = 0;
    void operator()() { this->run(); }
};

class ParseLobbyAction: public ParseAction {
private:
    LobbyCommandType& command;
    std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue;
    std::shared_ptr<Queue<GameImage>>& send_queue;
    InterfaceGamesMonitor& games_monitor;
    bool& in_lobby;

public:
    ParseLobbyAction(player_id_t& player_id, ServerProtocol& protocol, LobbyCommandType& command,
                     std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                     std::shared_ptr<Queue<GameImage>>& send_queue,
                     InterfaceGamesMonitor& games_monitor, bool& in_lobby);
    ~ParseLobbyAction();
    void run() override;
};

class ParsePlayerAction: public ParseAction {
private:
    PlayerCommandType& command;
    std::unique_ptr<ClientAction>& action;

public:
    ParsePlayerAction(player_id_t& player_id, ServerProtocol& protocol, PlayerCommandType& command,
                      std::unique_ptr<ClientAction>& action);
    ~ParsePlayerAction();
    void run() override;
};


#endif  // !FUNCTOR_PARSE_CLIENT_ACTION_H
