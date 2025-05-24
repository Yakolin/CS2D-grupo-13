#include "game_loop.h"

GameLoop::GameLoop(const std::string& game_name):
        game_name(game_name),
        game(game_name, "pepito"),
        send_queues(),
        recv_queue(std::make_shared<Queue<std::unique_ptr<ClientAction>>>(QUEUE_MAX_SIZE)),
        constant_rate_loop([this]() { return this->should_keep_running(); },
                           [this]() { this->step(); }),
        game_started(false) {}

GameLoop::~GameLoop() {}

void GameLoop::add_player(player_id_t& player_id,
                          std::shared_ptr<Queue<std::unique_ptr<ClientAction>>>& recv_queue,
                          std::shared_ptr<Queue<GameImage>>& send_queue) {
    recv_queue = this->recv_queue;
    send_queues.emplace_back(send_queue);
    this->game.add_player(player_id);
}

bool GameLoop::is_full()  // hay que ver como se configura el YAML y chequearlo ahi
{
    return false;
}

void GameLoop::run() { this->constant_rate_loop.execute(); }


void GameLoop::step() {
    try {
        std::unique_ptr<ClientAction> action = recv_queue->pop();
    } catch (const ClosedQueue& e) {
    } catch (const std::runtime_error& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}


void GameLoop::stop() {
    for (auto& send_queue: send_queues) {
        send_queue->close();
    }
    this->recv_queue->close();
}