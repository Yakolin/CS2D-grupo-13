#include "client_handler.h"

ClientHandler::ClientHandler(Socket &&socket, GamesMonitor &games_monitor) : socket(std::move(socket)), games_monitor(games_monitor), protocol(this->socket) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::run()
{
}
void ClientHandler::stop()
{
}