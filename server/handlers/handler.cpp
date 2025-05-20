#include "handler.h"

LobbyHandler::LobbyHandler(player_id_t client_id, Socket&& socket, GamesMonitor& games_monitor):
        Handler(client_id, std::move(socket)),
        games_monitor(games_monitor),
        protocol(this->socket) {}

LobbyHandler::~LobbyHandler() {}

void LobbyHandler::run() {
    while (this->should_keep_running()) {
        LobbyCommandType command = this->protocol.read_lobby_command();
        std::unique_ptr<InterfaceLobbyAction> action;
        ParseLobbyAction parser(this->client_id, this->protocol, command, action);
        parser();
        action->action(*this, this->games_monitor);
    }
}

void LobbyHandler::send(std::unique_ptr<InterfaceSenderLobby> action) {
    action->send(this->protocol);
}

PlayerHandler::PlayerHandler(
        player_id_t client_id, Socket&& socket,
        std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>>& recv_game_queue):
        Handler(client_id, std::move(socket)),
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
