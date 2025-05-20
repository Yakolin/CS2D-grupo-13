#include "client.h"

Client::Client(int& argc, char* argv[]): vista(argc, argv) {}

int Client::run() {

    vista.run();

    return 0;
}


Client::~Client() {}