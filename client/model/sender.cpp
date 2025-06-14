#include "sender.h"

Sender::Sender(Socket& socket,
               std::shared_ptr<Queue<std::unique_ptr<InterfaceClientAction>>>& send_queue):
        closed(false), protocol(socket), send_queue(send_queue) {}

Sender::~Sender() {}

void Sender::run() {

    try {
        while (!closed && this->should_keep_running()) {
            std::unique_ptr<InterfaceClientAction> client_action = this->send_queue->pop();
            client_action->action(this->protocol);
        }
    } catch (const ConnectionClosedException& e) {  // el cliente podria cerrar la conexion
        closed = true;
        this->send_queue->close();
    } catch (const ClosedQueue& e) {
        closed = true;
    }
}

void Sender::stop() { this->send_queue->close(); }
