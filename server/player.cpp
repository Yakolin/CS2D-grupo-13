#include "player.h"

Player::Player(Socket &&socket) : socket(std::move(socket)), sender(this->socket), receiver(this->socket) {}

Player::~PLayer() {}

void Player::run()
{
    this->sender.start();
    this->receiver.start();
}

void Player::stop()
{
    this->sender.stop();
    this->receiver.stop();
}
