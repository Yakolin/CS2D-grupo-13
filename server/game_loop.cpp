#include "game_loop.h"

GameLoop::GameLoop() : players(), recv_queue() {}
GameLoop::~GameLoop() = default;

void GameLoop::add_player(const Player &&player)
{
    players.push_back(std::make_unique<Player>(std::move(player)));
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