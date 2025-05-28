#include "server.h"

Server::Server(const char* port): port(port), acceptor(port), open(true) {}

Server::~Server() {}

void Server::run() {

    this->acceptor.start();

    while (this->open) {
        continue;
    }
    this->acceptor.stop();
    this->acceptor.join();
}

void Server::stop() { this->open = false; }