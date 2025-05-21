#include "sender.h"

Sender::Sender(Socket& socket, std::shared_ptr<Queue<GameImage>>& send_queue):
        send_queue(send_queue), protocol(socket), closed(false) {}

Sender::~Sender() {}

void Sender::run() {
    try {
        while (!this->closed && this->should_keep_running()) {
            GameImage game_image = this->send_queue->pop();
            this->protocol.send_game_image(game_image);
        }
    } catch (ClosedQueue& e) {
        this->closed = true;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        this->closed = true;
    }
}
