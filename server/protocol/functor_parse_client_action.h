#ifndef FUNCTOR_PARSE_CLIENT_ACTION_H
#define FUNCTOR_PARSE_CLIENT_ACTION_H

#include <memory>

#include "../../common/client_common_action.h"

#include "client_action.h"
#include "protocol.h"

class InterfaceLobbyAction;
class InterfacePlayerAction;

class Parse {
protected:
    ServerProtocol& protocol;

public:
    Parse(ServerProtocol& protocol): protocol(protocol) {}
    virtual ~Parse() = default;
    virtual void run() = 0;
    void operator()() { this->run(); }
};

class ParseLobbyAction: public Parse {
private:
    std::unique_ptr<InterfaceLobbyAction>& action;
    LobbyCommandType& command;

public:
    ParseLobbyAction(  // functor para las acciones de lobby
            ServerProtocol& protocol, LobbyCommandType& command,
            std::unique_ptr<InterfaceLobbyAction>& action);
    ~ParseLobbyAction();

    void run() override;
};

class ParsePlayerAction: public Parse {
private:
    player_id_t& player_id;
    std::unique_ptr<InterfacePlayerAction>& action;
    PlayerCommandType& command;

public:
    ParsePlayerAction(player_id_t& player_id, ServerProtocol& protocol, PlayerCommandType& command,
                      std::unique_ptr<InterfacePlayerAction>& action);
    ~ParsePlayerAction();
    void run() override;
};


#endif  // !FUNCTOR_PARSE_CLIENT_ACTION_H