#include  "client.h"

Client::Client( int& argc,  char *argv[]) : 
    controller(argc, argv)
    //protocolo() 
    {}

int Client::run() {
    #include <unistd.h>
#include <iostream>
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    std::cout << "Working directory: " << cwd << std::endl;
    controller.run();

    return 0;
}




Client::~Client() {}