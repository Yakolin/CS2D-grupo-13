#include "sender.h"

int contador = 0;

Sender::Sender(player_id_t& client_id, Socket& socket,
               std::shared_ptr<Queue<GameImage>>& send_queue):
        client_id(client_id), send_queue(send_queue), protocol(socket), closed(false) {}

Sender::~Sender() {}

void Sender::run() {
    try {
        while (!this->closed && this->should_keep_running()) {
            GameImage game_image = this->send_queue->pop();
            game_image.client_id = this->client_id;
            if (this->should_keep_running()) {
                this->protocol.send_game_image(game_image);
            }
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
