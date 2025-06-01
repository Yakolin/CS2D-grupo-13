#include "game_loop.h"

GameLoop::GameLoop(const std::string& game_name):
        game_name(game_name),
        game(game_name, "pepito"),
        send_queues(),
        recv_queue(std::make_shared<Queue<std::unique_ptr<ClientAction>>>(QUEUE_MAX_SIZE)),
        constant_rate_loop([this]() { return this->should_keep_running(); },
                           [this]() { this->step(); }),
        game_started(false) {}

GameLoop::~GameLoop() {
    if (Thread::is_alive()) {}
}

void GameLoop::add_player(player_id_t& player_id,
                          std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                          std::shared_ptr<Queue<GameImage>>& send_queue) {
    recv_queue = this->recv_queue;
    send_queues.emplace_back(send_queue);
    this->game.add_player(player_id);
}

bool GameLoop::is_full() { return (this->send_queues.size() == MAX_PLAYERS); }

bool GameLoop::waiting_for_players() { return !this->game_started; }

void GameLoop::run() {
    this->game_started = true;
    this->constant_rate_loop.execute();
}

void GameLoop::step() {
    try {
        std::unique_ptr<ClientAction> action = recv_queue->pop();
        game.process(*action);
        GameImage game_image = this->game.get_frame();
        this->broadcast(game_image);
    } catch (const ClosedQueue& e) {
        this->stop();
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        this->stop();
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Something went wrong in game_loop, and an unknown exception was caught."
                  << std::endl;
        this->stop();
    }
}

void GameLoop::broadcast(GameImage& game_image) {
    for (auto& send_queue: send_queues) {
        if (send_queue) {
            send_queue->push(game_image);
        } else {
            std::cerr << "Error: send_queue es nullptr" << std::endl;
        }
    }
}

void GameLoop::stop() {
    Thread::stop();
    this->recv_queue->close();
    std::unique_ptr<ClientAction> action;
    while (this->recv_queue->try_pop(action)) {}
}
