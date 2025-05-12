#include "player.h"

Player::Player(uint16_t &&player_id, Socket &&socket) : player_id(std::move(player_id)), socket(std::move(socket)), sender(this->socket), receiver(this->socket) {}

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
