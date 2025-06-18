#include "client.h"

Client::Client(int& argc, char* argv[]): vista(argc, argv) {}


int Client::run() {

    try {/*
        if(vista.showLobby()){
            vista.showGame();
           // vista.showScoreboard();       
        }
         */
        vista.showScoreboard();
    } catch (const std::exception& e) {
        std::cerr << "Excepción atrapada: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Excepción desconocida atrapada." << std::endl;
    }

    return 0;
}


Client::~Client() {}
