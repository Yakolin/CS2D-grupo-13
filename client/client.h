#ifndef CLIENT_H
#define CLIENT_H
#include "controller.h"
#include "protocoloClient.h"
#include <iostream>
#include <iostream>

class Client {

private:
    Controller controller;
    ProtocoloClient protocolo;
public:
    explicit Client(int& argc, char *argv[]) ;


    int run( );




    ~Client();

};

#endif // CLIENT_H
