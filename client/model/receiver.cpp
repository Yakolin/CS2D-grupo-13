#include "receiver.h"

Receiver::Receiver(Socket& socket, Queue<GameImage>& recv_queue):
        closed(false), protocol(socket), recv_queue(recv_queue) {}

Receiver::~Receiver() {}

void Receiver::run() {
    try {
        while (!closed && this->should_keep_running()) {
            GameImage game_image = this->protocol.read_game_image();
            this->recv_queue.push(game_image);
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
