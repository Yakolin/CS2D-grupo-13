#include "player.h"

Player::Player(Socket &&socket) : socket(std::move(socket)) sender(socket), receiver(socket) {}

Player::~PLayer() {}