#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>

#include "vista.h"

class Client {

private:
    Vista vista;

public:
    explicit Client(int& argc, char* argv[]);


    int run();
    ~Client();
};

#endif  // CLIENT_H
