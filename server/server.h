#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>

#include "acceptor.h"
#define QUIT "q"  // es la forma en la que paramos el acceptor, esta en el enunciado


class Server {
private:
    const char* port;
    Acceptor acceptor;
    bool open;

public:
    explicit Server(const char* port);

    ~Server();

    void run();
};  // namespace class Server

#endif  // !SERVER_H