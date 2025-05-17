#include "mapView.h"
MapView::MapView( const std::vector<std::vector<char>>& mapa_recibido, const int& width , const int& height) :
    backgroundTexture(),
    ventana(),
    renderer(),
    leyenda(),
    width(width) ,
    height(height),
    mapa(mapa_recibido),
    texturas()
{
    leyenda['#'] = "../assets/gfx/backgrounds/office.png";
    leyenda[' '] = "../assets/gfx/backgrounds/stone1.jpg";
    leyenda['~'] = "../assets/gfx/backgrounds/water4.jpg";

}
void MapView::load_textures() {
    for (const auto& par : leyenda) {
        SDL_Texture* tex = add_tiles(par.second);
        if (!tex) {
            std::cerr << "No se pudo cargar la textura para: " << par.first << std::endl;
        }
        texturas[par.first] = tex;
    }
}

bool MapView::initialize_sdl_video(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {  // Inicializa SDL con soporte para video
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool MapView::cargarTexturaFondo(SDL_Renderer* renderer) {

    SDL_Surface* surface = SDL_LoadBMP("../assets/gfx/tiles/default_aztec.bmp"); // Carga la imagen BMP desde la ruta dada a una superficie
    if (!surface) {
        std::cerr << "Error cargando imagen: " << SDL_GetError() << std::endl; 
        return false;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);  // Convierte la superficie a una textura que se puede usar para renderizar
    SDL_FreeSurface(surface);  

    if (!backgroundTexture) {
        std::cerr << "Error creando textura: " << SDL_GetError() << std::endl; 
        return false;
    }
    return true;
}

SDL_Texture* MapView::add_tiles(const std::string& img ){

    
    SDL_Surface* stoneSurface = IMG_Load(img.c_str());
    if (!stoneSurface) {
        std::cerr << "Error cargando imagen de piedra: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* tiles = SDL_CreateTextureFromSurface(renderer, stoneSurface);
    if (!tiles) 
        std::cerr << "Error creando textura de piedra: " << SDL_GetError() << std::endl;
    SDL_FreeSurface(stoneSurface);
    return tiles;
}


bool MapView::init_render_window(){
    ventana = SDL_CreateWindow("Mapa",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                width, height,
                                SDL_WINDOW_SHOWN);
    if (!ventana) {
        std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
        return false;
    }
    // Crea el renderer asociado a la ventana (con aceleración por hardware)
    renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Error al crear el renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    // Intenta cargar la textura de fondo
    if (!cargarTexturaFondo(renderer)) {
        return false;
    }
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        std::cerr << "Error inicializando SDL_image: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}



void MapView::complete_map_view(){

    SDL_Texture* tiles_stone;
    for (size_t i = 0; i < mapa.size(); i++) {
        for (size_t j = 0; j < mapa[i].size(); j++) {
            SDL_Rect destRect = { static_cast<int>(j * 32), static_cast<int>(i * 32), 32, 32 };
            char item = mapa[i][j];
            SDL_Texture* tex = texturas[item];
            if (tex)
                SDL_RenderCopy(renderer, tex, nullptr, &destRect);
        }
    }

}

void MapView::start_game() {

    if(!initialize_sdl_video() || !init_render_window()){
        return;
    }
    bool corriendo = true;
    SDL_Event evento;
    load_textures();

    while (corriendo) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT)
                corriendo = false;  // Se cierra la ventana
        }

        SDL_RenderClear(renderer);  // Limpia el render anterio

        complete_map_view(); // completar mapa
        
        SDL_RenderPresent(renderer);  // Muestra en pantalla el contenido renderizado
        SDL_Delay(16); // Espera aprox. 16ms para lograr ~60 FPS
    }
    IMG_Quit();

}


MapView::~MapView(){
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);  // Libera la textura
    if (renderer) SDL_DestroyRenderer(renderer);                  // Libera el renderer
    if (ventana) SDL_DestroyWindow(ventana);                      // Libera la ventana
    for (auto& par : texturas) {
        if (par.second) SDL_DestroyTexture(par.second);
    }
    SDL_Quit();                                                   // Cierra SDL

}