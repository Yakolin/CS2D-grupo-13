#include "server.h"

Server::Server(const char* port): port(port), acceptor(port), open(true) {}

Server::~Server() {}

void Server::run() {
    std::cout << "Aceptando clientes" << std::endl;
    this->acceptor.start();

    while (this->open) {
        char c = getchar();
        if (c == QUIT) {
            this->open = false;
            this->acceptor.stop();
            this->acceptor.join();
        }
    }
}
