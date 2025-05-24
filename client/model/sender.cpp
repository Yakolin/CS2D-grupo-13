#include "sender.h"

Sender::Sender(Socket& socket, std::shared_ptr<Queue<std::unique_ptr<InterfaceClientAction>>>& send_queue):
        closed(false), protocol(socket), send_queue(send_queue) {}

Sender::~Sender() {}

void Sender::run() {

    try {
        while (!closed && this->should_keep_running()) {
            std::unique_ptr<InterfaceClientAction> client_action = this->send_queue.pop();
            client_action->action(this->protocol);
        }
    } catch (ClosedQueue& e) {
        closed = true;
    } catch (const ConnectionClosedException& e) {  // el cliente podria cerrar la conexion
        closed = true;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        closed = true;
    }
}
