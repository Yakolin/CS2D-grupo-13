#include "sender.h"

Sender::Sender(Socket& socket): send_queue(QUEUE_MAX_SIZE), protocol(protocol), closed(false) {}

Sender::~Sender() {}

void Sender::send(GameImage& game_image) { this->send_queue.push(game_image); }

void Sender::run() {
    try {
        while (!this->closed && this->should_keep_running()) {
            GameImage game_image = this->send_queue.pop();
            this->protocol.send_game_image(game_image);
        }
    } catch (ClosedQueue& e) {
        this->closed = true;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        this->closed = true;
    }
}

void Sender::stop() { this->send_queue.close(); }