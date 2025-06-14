#include "gameConfig.h"

#include "manageTexture.h"


GameConfig::GameConfig():
    window_width(0),
    window_height(0),
    tile_width(32),
    tile_height(32),
    viewport_width(0),
    viewport_height(0),
    route_font(),
    size_font(),
    blanco(),
    font_menu(nullptr)
    {
        if (TTF_Init() == -1) {
            SDL_Log("Error al inicializar SDL_ttf: %s", TTF_GetError());
        }


        load("assets/configView.yaml");
        font_menu = TTF_OpenFont(route_font.c_str(), 15); // 18 es el tamaño
        if (!font_menu) {
            std::cerr << "ERROR: fuente no cargada - " << TTF_GetError() << std::endl;
            throw std::runtime_error("No se pudo cargar la fuente del menu.");
        }
        font_game =TTF_OpenFont("assets/gfx/fonts/sourcesans.ttf", 20); // 18 es el tamaño
        if (!font_game) {
            std::cerr << "ERROR: fuente no cargada - " << TTF_GetError() << std::endl;
            throw std::runtime_error("No se pudo cargar la fuente.");
        }
        colores = {
        {Color::ROJO,     {255,   0,   0, 255}},
        {Color::VERDE,    {  0, 255,   0, 255}},
        {Color::AZUL,     {  0,   0, 255, 255}},
        {Color::BLANCO,   {255, 255, 255, 255}},
        {Color::NEGRO,    {  0,   0,   0, 255}},
        {Color::AMARILLO, {255, 255,   0, 255}},
        {Color::CIAN,     {  0, 255, 255, 255}},
        {Color::MAGENTA,  {255,   0, 255, 255}},
        {Color::GRIS,     {128, 128, 128, 255}},
        {Color::NARANJA,  {255, 165,   0, 255}},
        {Color::VIOLETA,  {138,  43, 226, 255}},
        {Color::ROSADO,   {255, 192, 203, 255}}
    };

}

SDL_Color GameConfig::get_color(const Color& clave) {

    auto it = colores.find(clave);
    if (it != colores.end()) {
       // std::cout << "se encontró la textura para Object: " << static_cast<int>(clave) << std::endl;
        return it->second;
    }
    throw std::runtime_error("Textura no encontrada.");
}

TTF_Font* GameConfig::get_font_menu() { return font_menu; }
TTF_Font* GameConfig::get_font_game() { return font_game; }
void GameConfig::load(const std::string& file_path) {

    try {
        YAML::Node config = YAML::LoadFile(file_path);

        this->window_width = config["window"]["width"].as<int>();
        this->window_height = config["window"]["height"].as<int>();
        this->viewport_width = config["camera"]["viewport_logical_width"].as<int>();
        this->viewport_height = config["camera"]["viewport_logical_height"].as<int>();
        this->route_font = config["fuente"]["route_font_menu"].as<std::string>();
        this->size_font = config["fuente"]["size_fuente"].as<int>();
        this->blanco.r = config["blanco"]["r"].as<Uint8>();
        this->blanco.g = config["blanco"]["g"].as<Uint8>();
        this->blanco.b = config["blanco"]["b"].as<Uint8>();
        this->blanco.a = config["blanco"]["a"].as<Uint8>();
        this->intensity = config["fov"]["intensity"].as<int>();


    } catch (const YAML::Exception& e) {
        throw std::runtime_error("Error al leer archivo YAML: " + std::string(e.what()));
    }
}

int GameConfig::get_intensity(){return intensity;}

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
SDL_Color GameConfig::get_blanco() const { return blanco; }

int GameConfig::get_window_width() const { return window_width; }

int GameConfig::get_window_height() const { return window_height; }

int GameConfig::get_tile_width() const { return tile_width; }

int GameConfig::get_tile_height() const { return tile_height; }

int GameConfig::get_viewpost_height() const { return viewport_height; }

int GameConfig::get_viewpost_width() const { return viewport_width; }

int GameConfig::get_size_font() const { return size_font; }

std::string GameConfig::get_route_font() const { return route_font; }