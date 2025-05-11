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
    explicit Client();


    int run( int& argc,  char *argv[] );




    ~Client();

};

#endif // CLIENT_H
