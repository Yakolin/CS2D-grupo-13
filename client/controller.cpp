#include "controller.h"

Controller::Controller(int& argc,  char *argv[]) : gameView(argc, argv) {}
#define MAPA_AZTECA  "../assets/pueblito_azteca.txt"

//! mover a juegoView
std::vector<std::vector<char>> Controller::cargar_mapa(const std::string& archivo) {
    
    std::vector<std::vector<char>> mapa;
    if (archivo.empty()) {
        throw std::runtime_error("Error cargando archivo mapa");
        return mapa;
    }

    std::ifstream entrada(archivo);
    std::string linea;

    while (getline(entrada, linea)) {
        std::vector<char> fila;
        for (char c : linea) {
            fila.push_back(c);
        }
        mapa.push_back(fila);
    }
    return mapa;
}

void Controller::run() {
    // gameView.run_menu();
    std::vector<std::vector<char>> mapa = cargar_mapa(MAPA_AZTECA);
    MapView map(mapa, 1216 , 544);
    map.start_game();

}