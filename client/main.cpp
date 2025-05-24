
#include <iostream>
#include "client.h"
#include "lobbyView.h"

const int ERROR_CLIENT =1;

int main(int argc, char* argv[]) {
    if(argc < 2){
        std::cout << "no hay suficientes argumentos, enviar hostname puerto\n";
        return ERROR_CLIENT;
    }

    Client client(argc, argv);
    return client.run();
}
