#include "receiver.h"

LobbyReceiver::LobbyReceiver(
        player_id_t& player_id, Socket& socket,
        std::shared_ptr<Queue<std::unique_ptr<InterfaceLobbyAction>>>& recv_lobby_queue):
        Receiver(player_id, socket), recv_lobby_queue(recv_lobby_queue) {}

LobbyReceiver::~LobbyReceiver() {}

void LobbyReceiver::run() {
    try {
        while (!this->closed && this->should_keep_running()) {
            LobbyCommandType command = this->protocol.read_lobby_command();
            std::unique_ptr<InterfacePlayerAction> action =
        }

    } catch (ClosedQueue& e) {
        this->closed = true;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        closed = true;
    }
}