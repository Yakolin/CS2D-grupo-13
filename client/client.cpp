#include "client.h"

#include <iomanip>


Client::Client(int& argc, char* argv[]): vista(argc, argv) {}


int Client::run() {

    try {
        if (vista.showLobby()) {
            EndGameInfo end_game_info = vista.showGame();
            vista.showScoreboard(end_game_info);
        }

    } catch (const std::exception& e) {
        std::cerr << "Excepción atrapada: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Excepción desconocida atrapada." << std::endl;
    }

    return 0;
}


Client::~Client() {}
