#include  "client.h"

Client::Client() : controller() , protocolo() {}

int Client::run( int& argc,  char *argv[]) {
    controller.run(argc, argv);

    return 0;
}




Client::~Client() {}