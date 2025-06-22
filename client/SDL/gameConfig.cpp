#include "gameConfig.h"

#include "manageTexture.h"


GameConfig::GameConfig():
    window_width(0),
    window_height(0),
    tile_width(32),
    tile_height(32),
    viewport_width(0),
    viewport_height(0),
    font_menu(nullptr),
    font_hud(nullptr)
    {
        if (TTF_Init() == -1) {
            SDL_Log("Error al inicializar SDL_ttf: %s", TTF_GetError());
        }

        load("assets/configView.yaml");
        load_font("assets/gfx/fonts/cs_regular.ttf",font_menu,15);
        load_font("assets/gfx/fonts/sourcesans.ttf",font_game,30);
        load_font("assets/gfx/fonts/DS-DIGIB.TTF",font_hud,30);
        colores = {
        {Color::ROJO,     {255,   0,   0, 255}},{Color::VERDE,    {  0, 255,   0, 255}},
        {Color::AZUL,     {  0,   0, 255, 255}},{Color::BLANCO,   {255, 255, 255, 255}},
        {Color::NEGRO,    {  0,   0,   0, 255}},{Color::AMARILLO, {255, 255,   0, 255}},
        {Color::CIAN,     {  0, 255, 255, 255}},{Color::MAGENTA,  {255,   0, 255, 255}},
        {Color::GRIS,     {128, 128, 128, 255}},{Color::NARANJA,  {255, 165,   0, 255}},
        {Color::VIOLETA,  {138,  43, 226, 255}},{Color::ROSADO,   {255, 192, 203, 255}}
    };
    translucent_colors = {
        {ColorTranslucent::ROJO,     {255, 0, 0, 50}},
        {ColorTranslucent::VERDE,    {0, 255, 0, 50}},
        {ColorTranslucent::AZUL,     {0, 0, 255, 50}},
        {ColorTranslucent::BLANCO,   {255, 255, 255, 50}},
        {ColorTranslucent::NEGRO,    {0, 0, 0, 50}},
        {ColorTranslucent::AMARILLO, {255, 255, 0, 50}},
        {ColorTranslucent::CIAN,     {0, 255, 255, 50}},
        {ColorTranslucent::MAGENTA,  {255, 0, 255, 50}},
        {ColorTranslucent::GRIS,     {128, 128, 128, 50}},
        {ColorTranslucent::NARANJA,  {255, 165, 0, 50}},
        {ColorTranslucent::VIOLETA,  {138, 43, 226, 50}},
        {ColorTranslucent::ROSADO,   {255, 192, 203, 50}},
    };
}
void GameConfig::load_font(const std::string& route, TTF_Font*& font, const int& size){
    font =TTF_OpenFont(route.c_str(), size); 
    if (!font) {
        throw std::runtime_error("No se pudo cargar la fuente.");
    }
}

void GameConfig::get_dimension(SDL_Texture* texture_player, int& width_img, int& height_img) {
    SDL_QueryTexture(texture_player, nullptr, nullptr, &width_img, &height_img);
}

SDL_Color GameConfig::get_color(const Color& clave) {

    auto it = colores.find(clave);
    if (it != colores.end()) {
       // std::cout << "se encontró la textura para Object: " << static_cast<int>(clave) << std::endl;
        return it->second;
    }
    throw std::runtime_error("Textura no encontrada.");
}

SDL_Color GameConfig::get_color_translucent(const ColorTranslucent& clave)  {

    auto it = translucent_colors.find(clave);
    if (it != translucent_colors.end()) {
       // std::cout << "se encontró la textura para Object: " << static_cast<int>(clave) << std::endl;
        return it->second;
    }
    throw std::runtime_error("Textura no encontrada.");
}
TTF_Font* GameConfig::get_font_menu() { return font_menu; }
TTF_Font* GameConfig::get_font_game() { return font_game; }
TTF_Font* GameConfig::get_font_hud() { return font_hud; }

void GameConfig::load(const std::string& file_path) {

    try {
        YAML::Node config = YAML::LoadFile(file_path);

        this->window_width = config["window"]["width"].as<int>();
        this->window_height = config["window"]["height"].as<int>();
        this->viewport_width = config["camera"]["viewport_logical_width"].as<int>();
        this->viewport_height = config["camera"]["viewport_logical_height"].as<int>();
        this->intensity = config["fov"]["intensity"].as<int>();
        this->volumen_game = config["volumen"].as<int>();


    } catch (const YAML::Exception& e) {
        throw std::runtime_error("Error al leer archivo YAML: " + std::string(e.what()));
    }
}



int GameConfig::get_intensity(){return intensity;}
int GameConfig::get_volumen(){return volumen_game;}

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

int GameConfig::get_window_width() const { return window_width; }

int GameConfig::get_window_height() const { return window_height; }

int GameConfig::get_tile_width() const { return tile_width; }

int GameConfig::get_tile_height() const { return tile_height; }

int GameConfig::get_viewpost_height() const { return viewport_height; }

int GameConfig::get_viewpost_width() const { return viewport_width; }
