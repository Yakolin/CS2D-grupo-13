#include "game_loop.h"

GameLoop::GameLoop(const std::string &game_name, const uint16_t &number_of_players) : players(), recv_queue(), game(game_name, number_of_players), game_started(false) {}
GameLoop::~GameLoop() {}

void GameLoop::add_player(std::unique_ptr<Player> player)
{
    players.push_back(std::move(player));
}

void GameLoop::start()
{
    for (auto &player : players)
    {
        player->start();
    }
    game_started = true;
    Thread::start();
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