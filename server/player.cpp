#include "player.h"

Player::Player(uint16_t &&player_id, Socket &&socket, Queue<std::shared_ptr<PlayerAction>> &recv_queue) : player_id(std::move(player_id)), socket(std::move(socket)), sender(this->socket), receiver(this->player_id, this->socket, recv_queue) {}

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
