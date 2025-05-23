#ifndef FUNCTOR_PARSE_CLIENT_ACTION_H
#define FUNCTOR_PARSE_CLIENT_ACTION_H

#include <memory>

#include "../../common/client_common_action.h"

#include "client_action.h"
#include "protocol.h"

class ParsePlayerAction {
private:
    player_id_t& player_id;
    ServerProtocol& protocol;
    PlayerCommandType& command;
    std::unique_ptr<ClientAction>& action;

public:
    ParsePlayerAction(player_id_t& player_id, ServerProtocol& protocol, PlayerCommandType& command,
                      std::unique_ptr<ClientAction>& action);
    ~ParsePlayerAction();
    void run();
    void operator()() { this->run(); }
};


#endif  // !FUNCTOR_PARSE_CLIENT_ACTION_H