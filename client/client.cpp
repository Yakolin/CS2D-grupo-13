#include  "client.h"

Client::Client( int& argc,  char *argv[]) : controller(argc, argv), protocolo() {}

int Client::run() {
    controller.run();

    return 0;
}




Client::~Client() {}