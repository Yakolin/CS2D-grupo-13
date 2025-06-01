#include "gameConfig.h"

GameConfig::GameConfig():
    window_width(0),
    window_height(0),
    tile_width(32),
    tile_height(32)
    {
        load("assets/configView.yaml");
    }

void GameConfig::load(const std::string& file_path){
    
    try {
        YAML::Node config = YAML::LoadFile(file_path);

        this->window_width = config["window"]["width"].as<int>();
        this->window_height = config["window"]["height"].as<int>();

    } catch (const YAML::Exception& e) {
        throw std::runtime_error("Error al leer archivo YAML: " + std::string(e.what()));
    }

}

std::vector<std::vector<char>> GameConfig::load_map(const std::string& archivo) {

    std::vector<std::vector<char>> mapa;
    if (archivo.empty()) {
        throw std::runtime_error("Error cargando archivo mapa");
        return mapa;
    }

    std::ifstream entrada(archivo);
    std::string linea;

    while (getline(entrada, linea)) {
        std::vector<char> fila;
        for (char c: linea) {
            fila.push_back(c);
        }
        mapa.push_back(fila);
    }
    entrada.close(); 
    return mapa;
}

void GameConfig::calculate_tile_size( const int& cols,const  int& rows) {
    if (cols <= 0 || rows <= 0) {
        throw std::invalid_argument("La cantidad de columnas y filas debe ser positiva");
    }

    tile_width = window_width / cols;
    tile_height = window_height / rows;
}
int GameConfig::get_window_width() const {
    return window_width;
}

int GameConfig::get_window_height() const {
    return window_height;
}

int GameConfig::get_tile_width() const {
    return tile_width;
}

int GameConfig::get_tile_height() const {
    return tile_height;
}



