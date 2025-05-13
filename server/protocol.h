#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "common/socket.h"
#include "common/lobby_action.h"
#include <string>
#include "common/game_image.h"
#include <vector>

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
    void send_game_image(GameImage &game_image);
};

#endif // !PROTOCOL_H