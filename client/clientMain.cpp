
#include <iostream>
#include "client.h"

int main(int argc, char *argv[]) {
    Client client(argc, argv);
    return client.run();
}