#include "client_handler.h"

ClientHandler::ClientHandler(player_id_t player_id, Socket&& socket, GamesMonitor& games_monitor):
        player_id(player_id),
        socket(std::move(socket)),
        send_queue(std::make_shared<Queue<GameImage>>(QUEUE_MAX_SIZE)),
        sender(this->socket, this->send_queue),
        receiver(this->player_id, this->socket, this->send_queue, games_monitor) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::start() {
    this->receiver.start();
    this->sender.start();
}

bool ClientHandler::is_alive() { return (this->receiver.is_alive() && this->sender.is_alive()); }

void ClientHandler::stop() { this->send_queue->close(); }