#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "common/socket.h"
#include "common/lobby_action.h"
#include <string>

class ServerProtocol
{
private:
    Socket &socket;

public:
    explicit ServerProtocol(Socket &socket);
    ~ServerProtocol();
    LobbyAction read_lobby_action();
    std::string read_name();
    void send_games(std::vector<std::string> &game_names);
};

#endif // !PROTOCOL_H