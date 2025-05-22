#ifndef CLIENT_H
#define CLIENT_H
#include "vista.h"
#include <iostream>

class Client {

private:
    Vista vista;
public:
    explicit Client(int& argc, char *argv[]) ;


    int run( );


    ~Client();

};

#endif // CLIENT_H
