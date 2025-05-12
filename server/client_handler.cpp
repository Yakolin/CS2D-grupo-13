#include "client_handler.h"

ClientHandler::ClientHandler(uint16_t client_id, Socket &&socket, GamesMonitor &games_monitor) : client_id(client_id), socket(std::move(socket)), games_monitor(games_monitor), protocol(this->socket), in_lobby(true) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::run()
{
    try
    {
        while (this->should_keep_running() && in_lobby)
        {
            LobbyAction action = this->protocol.read_lobby_action();
            switch (action)
            {
            case LobbyAction::CREATE:
            {
                std::string game_name;
                Player player(this->socket);
                this->games_monitor.create_game(game_name, player);
                break;
            }
            }
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void ClientHandler::stop()
{
}