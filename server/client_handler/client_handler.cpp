#include "client_handler.h"

ClientHandler::ClientHandler(uint16_t client_id, Socket&& socket, GamesMonitor& games_monitor):
        client_id(client_id), socket(std::move(socket)), receiver(), sender(), in_lobby(true) {}

ClientHandler::~ClientHandler() {}

void ClientHandler::stop_threads() {
    if (this->receiver) {
        if (this->receiver->is_alive()) {
            this->receiver->stop();
            this->receiver->join();
        }
    }
    if (this->sender) {
        if (this->receiver->is_alive()) {
            this->sender->stop();
            this->sender->join();
        }
    }
}

void ClientHandler::run_lobby(GamesMonitor& games_monitor) {
    std::shared_ptr<Queue<std::unique_ptr<InterfaceLobbyAction>>> lobby_queue =
            std::make_shared<Queue<std::unique_ptr<InterfaceLobbyAction>>>(QUEUE_MAX_SIZE);
    this->receiver = std::make_unique<LobbyReceiver>(this->client_id, this->socket, lobby_queue,
                                                     games_monitor);
    this->sender = std::make_unique<LobbySender>(this->socket);
    this->receiver->start();
    this->sender->start();
    while (this->in_lobby) {
        std::unique_ptr<InterfaceLobbyAction> action = lobby_queue->pop();
        action->action(games_monitor);
    }
}

void ClientHandler::send_handshake() { this->sender-> }

void ClientHandler::run_game() { this->stop_threads(); }

void ClientHandler::stop() {
    this->stop_threads();
    this->socket.shutdown(2);
    this->socket.close();
}
