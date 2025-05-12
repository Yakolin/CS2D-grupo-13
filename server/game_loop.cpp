#include "game_loop.h"

GameLoop::GameLoop(const std::string &game_name) : players(), recv_queue(), game(game_name), game_started(false) {}
GameLoop::~GameLoop() {}

void GameLoop::add_player(const uint16_t &player_id, Socket &socket)
{
    players.push_back(std::make_unique<Player>(std::move(player_id), std::move(socket), recv_queue));
}

bool GameLoop::is_full() // hay que ver como se configura el YAML y chequearlo ahi
{
    return false;
}

void GameLoop::start()
{
    for (auto &player : players)
    {
        player->start();
    }
    game_started = true;
    Thread::start(); // esto pone a ejecutar el thread, ejecuta la funcion run
}

void GameLoop::run() // aca iria el constant rate loop
{
}

void GameLoop::stop()
{
    for (auto &player : players)
    {
        player->stop();
    }
}