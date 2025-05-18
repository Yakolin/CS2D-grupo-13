#include "controller.h"
#include "playerView.h"
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
    const float speed = 2.5f;
    float x = 5;
    float y = 5;
    try{
        // gameView.run_menu();
        std::vector<std::vector<char>> mapa = cargar_mapa(MAPA_AZTECA);
        //MapView map(mapa, 1216 , 544);
        MapView map(mapa, 500 , 500);
        PlayerView player(x,y,"../assets/gfx/terrorist/t1_1.png",speed);
        if(!map.init_game()){
            throw std::runtime_error("No se pudo inicializar el juego visual");
            return;
        }
        map.add_player(player);
        map.show_map();
    }catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }


}