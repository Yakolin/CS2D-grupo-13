#include "player.h"

Player::Player(uint16_t &&player_id, Socket &&socket) : player_id(std::move(player_id)), socket(std::move(socket)), sender(this->socket), receiver(this->socket) {}

Player::~Player() {}

void Player::start()
{
    this->sender.start();
    this->receiver.start();
}

void Player::stop()
{
    this->socket.shutdown(2);
    this->socket.close();
    this->sender.stop();
    this->receiver.stop();
    this->sender.join();
    this->receiver.join();
}
