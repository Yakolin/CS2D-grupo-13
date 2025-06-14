#include "receiver.h"

Receiver::Receiver(Socket& socket, std::shared_ptr<Queue<GameImage>>& recv_queue):
        closed(false), protocol(socket), recv_queue(recv_queue) {}

Receiver::~Receiver() {}

void Receiver::run() {
    try {
        while (!closed && this->should_keep_running()) {
            GameImage game_image = this->protocol.read_game_image();
            this->recv_queue->push(std::move(game_image));
        }
    } catch (const ConnectionClosedException& e) {  // el cliente podria cerrar la conexion
        closed = true;
        this->recv_queue->close();
    }
}

void Receiver::stop() { this->recv_queue->close(); }
