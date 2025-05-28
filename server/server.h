#ifndef SERVER_H
#define SERVER_H

#include <atomic>
#include <iostream>
#include <string>

#include "acceptor.h"

#define QUIT 'q'

class Server {
private:
    const char* port;
    Acceptor acceptor;
    std::atomic<bool> open;

public:
    explicit Server(const char* port);

    ~Server();

    void run();
};

#endif  // !SERVER_H
