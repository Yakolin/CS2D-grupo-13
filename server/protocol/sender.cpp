#include "sender.h"

Sender::Sender(Socket& socket, std::shared_ptr<Queue<GameImage>>& send_queue):
        send_queue(send_queue), protocol(socket), closed(false) {}

Sender::~Sender() {}

void Sender::run() {
    try {
        while (!this->closed && this->should_keep_running()) {
            std::cout << "recibo la imagen" << std::endl;
            GameImage game_image = this->send_queue->pop();
            this->protocol.send_game_image(game_image);
        }
    } catch (const ConnectionClosedException& e) {
        std::cout << "The client closed the connection" << std::endl;
        this->closed = true;
    } catch (ClosedQueue& e) {
        this->closed = true;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught in sender."
                  << std::endl;
        this->closed = true;
    }
}

void Sender::stop() {
    Thread::stop();
    this->send_queue->close();
}
