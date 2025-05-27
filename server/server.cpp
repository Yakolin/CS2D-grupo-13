#include "server.h"

Server::Server(const char* port): port(port), acceptor(port), open(true) {}

Server::~Server() {}

void Server::run() {
    this->acceptor.start();  // es un thread, debe ser iniciado
    std::string command;
    while (this->open && this->acceptor.is_alive()) {
        std::getline(std::cin, command);
        if (command == QUIT) {
            this->acceptor.stop();
            this->open = false;
        }
    }

    this->acceptor.join();  // es un thread, debe ser joinado
}
