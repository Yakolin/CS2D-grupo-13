#include "sender.h"

LobbySender::LobbySender(Socket& socket): Sender(socket), send_lobby_queue(QUEUE_MAX_SIZE) {}

LobbySender::~LobbySender() {}

void LobbySender::send(std::unique_ptr<InterfaceSenderLobby>& action) {
    this->send_lobby_queue.push(std::move(action));
}

void LobbySender::run() {
    try {
        while (!this->closed && this->should_keep_running()) {
            std::unique_ptr<InterfaceSenderLobby> action = this->send_lobby_queue.pop();
            action->send(this->protocol);
        }
    } catch (ClosedQueue& e) {
        this->closed = true;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        this->closed = true;
    }
}

void LobbySender::stop() { this->send_lobby_queue.close(); }


GameSender::GameSender(Socket& socket): Sender(socket), send_game_queue(QUEUE_MAX_SIZE) {}

GameSender::~GameSender() {}

void GameSender::send(GameImage& game_image) { this->send_game_queue.push(game_image); }

void GameSender::run() {
    try {
        while (!this->closed && this->should_keep_running()) {
            GameImage game_image = this->send_game_queue.pop();
            this->protocol.send_game_image(game_image);
        }
    } catch (ClosedQueue& e) {
        this->closed = true;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        this->closed = true;
    }
}

void GameSender::stop() { this->send_game_queue.close(); }