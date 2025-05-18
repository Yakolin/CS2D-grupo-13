#include "client_handler.h"

ClientHandler::ClientHandler(uint16_t client_id, Socket&& socket, GamesMonitor& games_monitor):
        client_id(client_id),
        socket(std::move(socket)),
        games_monitor(games_monitor),
        receiver(),
        sender(),
        in_lobby(true) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::run_lobby() {}

void ClientHandler::stop() {
    this->socket.shutdown(2);
    this->socket.close();
}