
#include <iostream>

#include "client.h"


const int ERROR_CLIENT = 1;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "no hay suficientes argumentos, enviar hostname puerto\n";
        return ERROR_CLIENT;
    }
    try {

        Client client(argc, argv);
        client.run();

    } catch (const std::exception& e) {
        std::cerr << "Excepción atrapada: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Excepción desconocida atrapada." << std::endl;
    }

    return 0;
}
