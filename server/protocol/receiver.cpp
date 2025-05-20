#include "receiver.h"

Receiver::Receiver(player_id_t& player_id, Socket& socket,
                   std::shared_ptr<Queue<std::unique_ptr<InterfacePlayerAction>>>& recv_queue):
        player_id(player_id), protocol(socket), recv_queue(recv_queue), closed(false) {}

Receiver::~Receiver() {}


void Receiver::run() {
    try {
        while (!this->closed && this->should_keep_running()) {
            PlayerCommandType command = this->protocol.read_player_command();
            std::unique_ptr<InterfacePlayerAction> action;
            ParsePlayerAction parser(this->player_id, this->protocol, command, action);
            parser();
            if (!this->closed) {
                this->recv_queue->push(std::move(action));
            }
        }

    } catch (ClosedQueue& e) {
        this->closed = true;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        closed = true;
    }
}