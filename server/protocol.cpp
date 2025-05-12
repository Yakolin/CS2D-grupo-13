#include "protocol.h"

ServerProtocol::ServerProtocol(Socket &socket) : socket(socket) {}

ServerProtocol::~ServerProtocol() {}

LobbyAction ServerProtocol::read_lobby_action()
{
    uint8_t action;
    this->socket.recvall(&action, sizeof(action));
    return static_cast<LobbyAction>(action);
}

std::string ServerProtocol::read_name()
{
    return std::string();
}

void ServerProtocol::send_games(std::vector<std::string> &game_names)
{
    uint8_t game_count = game_names.size();
    this->socket.sendall(&game_count, sizeof(game_count));
    for (const auto &game_name : game_names)
    {
        uint8_t name_length = game_name.size();
        this->socket.sendall(&name_length, sizeof(name_length));
        this->socket.sendall(game_name.data(), name_length);
    }
}
void ServerProtocol::send_game_image(GameImage &game_image)
{
    this->socket.sendall(&game_image, sizeof(game_image));
}
