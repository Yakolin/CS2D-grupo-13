#include "player_handler.h"

PlayerHandler::PlayerHandler(
        player_id_t&& client_id, Socket&& socket,
        std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>>& recv_game_queue):
        client_id(std::move(client_id)),
        socket(std::move(socket)),
        receiver(this->client_id, this->socket, recv_game_queue),
        sender(this->socket) {}

PlayerHandler::~PlayerHandler() {}

void PlayerHandler::start() {
    this->receiver.start();
    this->sender.start();
}

void PlayerHandler::send(GameImage& game_image) { this->sender.send(game_image); }

void PlayerHandler::stop() {
    this->receiver.stop();
    this->sender.stop();
    this->socket.shutdown(2);
    this->socket.close();
}
