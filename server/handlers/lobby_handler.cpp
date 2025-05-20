#include "lobby_handler.h"

LobbyHandler::LobbyHandler(player_id_t client_id, Socket&& socket, GamesMonitor& games_monitor):
        client_id(client_id),
        socket(std::move(socket)),
        games_monitor(games_monitor),
        protocol(this->socket),
        in_lobby(true) {}

LobbyHandler::~LobbyHandler() {}

void LobbyHandler::run() {
    try {
        while (this->should_keep_running() && in_lobby) {
            LobbyCommandType command = this->protocol.read_lobby_command();
            std::unique_ptr<InterfaceLobbyAction> action;
            ParseLobbyAction parser(this->protocol, command, action);
            parser();
            action->action(*this, this->games_monitor);
        }
    } catch (const ConnectionClosedException& e) {}
}

void LobbyHandler::send_handshake() {
    this->protocol.send_player_id(this->client_id);
    this->in_lobby = false;
}

void LobbyHandler::send_list_games(std::vector<std::string>& list_games) {
    this->protocol.send_list_games(list_games);
}


std::unique_ptr<PlayerHandler> LobbyHandler::start_game(
        std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>>& recv_player_queue) {
    this->send_handshake();
    std::unique_ptr<PlayerHandler> player_handler = std::make_unique<PlayerHandler>(
            std::move(this->client_id), std::move(this->socket), recv_player_queue);
    this->in_lobby = false;
    return player_handler;
}