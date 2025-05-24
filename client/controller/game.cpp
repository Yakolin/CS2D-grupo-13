#include "game.h"

Game::Game(Socket& skt):
        socket(),
        send_queue(std::make_shared<Queue>(MAX_QUEUE_SIZE)),
        recv_queue(std::make_shared<Queue>(MAX_QUEUE_SIZE)),
        receiver(this->socket, this->recv_queue),
        sender(this->socket, this->send_queue),
        command_handler(this->send_queue, this->socket),
        constant_rate_loop([this]() { return this->receiver.should_keep_running(); },
                           [this]() { this->step(); }) {}

Game::~Game() {}

void Game::update_image() {
    GameImage new_image;
    while (this->recv_queue->try_pop(new_image)) {
        // el renderizado de imagen habria un orden de renderizado o algo asi
    }
}


void Game::step() {
    this->command_handler.run();
    this->update_image();
}
void Game::run_game() {
    this->receiver.start();
    this->sender.start();
    this->constant_rate_loop().execute();
}
