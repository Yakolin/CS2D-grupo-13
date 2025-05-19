#ifndef FUNCTOR_PARSE_CLIENT_ACTION_H
#define FUNCTOR_PARSE_CLIENT_ACTION_H

#include <memory>

#include "../common/client_common_action.h"

#include "client_action.h"
#include "protocol.h"

class Parse {
protected:
    player_id_t& player_id;
    ServerProtocol& protocol;

public:
    Parse(player_id_t player_id, ServerProtocol& protocol):
            player_id(player_id), protocol(protocol) {}
    virtual ~Parse() = default;
    virtual void run() = 0;
    void operator()() { this->run(); }
};

class ParseLobbyAction: public Parse {
private:
    std::unique_ptr<InterfaceLobbyAction>& action;
    LobbyCommandType& command;

public:
    ParseLobbyAction(player_id_t& player_id,  // functor para las acciones de lobby
                     ServerProtocol& protocol, LobbyCommandType& command,
                     std::unique_ptr<InterfaceLobbyAction>& action);
    ~ParseLobbyAction();

    void run() override;
};

class ParsePlayerAction: public Parse {
private:
    std::unique_ptr<InterfacePlayerAction>& action;
    PlayerCommandType& command;

public:
    ParsePlayerAction(player_id_t& player_id, ServerProtocol& protocol, PlayerCommandType& command,
                      std::unique_ptr<InterfacePlayerAction>& action);
    ~ParsePlayerAction();
    void run() override;
};


#endif  // !FUNCTOR_PARSE_CLIENT_ACTION_H