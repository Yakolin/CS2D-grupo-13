#include "game_loop.h"

GameLoop::GameLoop() : players(), recv_queue() {}
GameLoop::~GameLoop() = default;

void GameLoop::add_player(std::unique_ptr<Player> player)
{
    players.push_back(std::move(player));
}

void GameLoop::run()
{
}

void GameLoop::stop()
{
    for (auto &player : players)
    {
        player->stop();
    }
}