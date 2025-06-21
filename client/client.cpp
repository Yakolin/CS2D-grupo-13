#include <iomanip>
#include "client.h"

Client::Client(int& argc, char* argv[]): vista(argc, argv) {}



int Client::run() {

    try {
        if (vista.showLobby()) {
            std::map<player_id_t, InfoPlayer> table = vista.showGame();
          //  imprimir_tabla_jugadores(table);
            vista.showScoreboard(table);
        }
    } catch (const std::exception& e) {
        std::cerr << "Excepción atrapada: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Excepción desconocida atrapada." << std::endl;
    }

    return 0;
}


Client::~Client() {}
