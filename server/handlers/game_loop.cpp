#include "game_loop.h"

GameLoop::GameLoop(LobbyHandler&& client_creator, const std::string& game_name):
        players(),
        recv_queue(std::make_shared<Queue<std::unique_ptr<InterfacePlayerAction>>>(QUEUE_MAX_SIZE)),
        game_started(false) {
    this->add_player(std::move(client_creator));
}

GameLoop::~GameLoop() {}

void GameLoop::add_player(LobbyHandler&& client_to_add) {
    players.emplace_back(
            std::make_unique<PlayerHandler>(std::move(client_to_add), this->recv_queue));
}

bool GameLoop::is_full()  // hay que ver como se configura el YAML y chequearlo ahi
{
    return false;
}

void GameLoop::start() {
    for (auto& player: players) {
        player->start();
    }
    game_started = true;
    Thread::start();  // esto pone a ejecutar el thread, ejecuta la funcion run
}

void GameLoop::run() {}


void GameLoop::step() {}


void GameLoop::stop() {
    for (auto& player: players) {
        player->stop();
    }
}