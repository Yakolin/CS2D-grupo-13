#include "mapView.h"
MapView::MapView() :
    backgroundTexture(),
    ventana(),
    renderer(),
    wall("../assets/gfx/backgrounds/aztec.png"),
    stone("../assets/gfx/backgrounds/stone1.jpg"),
    water("../assets/gfx/backgrounds/water4.jpg"),
    fil(16),
    col(16),
    mapa{{
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,0,0,1,1,1,1,0,1,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1},
        {1,0,1,0,1,1,1,1,0,1,1,1,1,0,0,1},
        {1,0,1,0,1,0,0,1,0,1,0,0,1,0,0,1},
        {1,0,1,0,1,0,0,1,0,1,0,0,1,0,0,1},
        {1,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1},
        {1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,0,1,0,1,0,1,0,1},
        {1,0,1,1,1,1,1,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    }}
{
    // resto del constructor
}


// Carga una imagen BMP como textura de fondo
bool MapView::cargarTexturaFondo(SDL_Renderer* renderer) {
    // Carga la imagen BMP desde la ruta dada a una superficie
    SDL_Surface* surface = SDL_LoadBMP("../assets/gfx/tiles/default_aztec.bmp");
    if (!surface) {
        // Si falló la carga, muestra el error en consola y retorna false
        std::cerr << "Error cargando imagen: " << SDL_GetError() << std::endl;
        return false;
    }

    // Convierte la superficie a una textura que se puede usar para renderizar
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
    // Libera la memoria de la superficie (ya no se necesita)
    SDL_FreeSurface(surface);

    if (!backgroundTexture) {
        // Si no se pudo crear la textura, muestra el error y retorna false
        std::cerr << "Error creando textura: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;  // La textura se cargó exitosamente
}

// Inicia el juego/render del mapa
void MapView::start_game() {

    // Inicializa SDL con soporte para video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return;
    }

    // Crea la ventana principal centrada en pantalla con tamaño 800x600
    ventana = SDL_CreateWindow("Mapa",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               800, 600,
                               SDL_WINDOW_SHOWN);
    if (!ventana) {
        std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // Crea el renderer asociado a la ventana (con aceleración por hardware)
    renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Error al crear el renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    // Intenta cargar la textura de fondo
    if (!cargarTexturaFondo(renderer)) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    // Bucle principal del juego (eventos + renderizado)
    bool corriendo = true;
    SDL_Event evento;
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        std::cerr << "Error inicializando SDL_image: " << IMG_GetError() << std::endl;
        // Manejar error
    }
    SDL_Surface* stoneSurface = IMG_Load(stone.c_str());
    if (!stoneSurface) {
        std::cerr << "Error cargando imagen de piedra: " << IMG_GetError() << std::endl;
        // Maneja el error (puedes salir o usar una textura por defecto)
    }
    SDL_Surface* wallSurface = IMG_Load(wall.c_str());
    if (!wallSurface) {
        std::cerr << "Error cargando imagen de pared: " << IMG_GetError() << std::endl;
        // Maneja el error
    }
    SDL_Texture* tiles_stone = SDL_CreateTextureFromSurface(renderer, stoneSurface);
    if (!tiles_stone) {
        std::cerr << "Error creando textura de piedra: " << SDL_GetError() << std::endl;
    }
    SDL_Texture* tiles_wall = SDL_CreateTextureFromSurface(renderer, wallSurface);
    if (!tiles_wall) {
        std::cerr << "Error creando textura de pared: " << SDL_GetError() << std::endl;
    }

    while (corriendo) {
        // Maneja eventos (teclado, mouse, cerrar ventana, etc.)
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT)
                corriendo = false;  // Se cierra la ventana
        }

        SDL_RenderClear(renderer);  // Limpia el render anterio

        // completo el mapa
        for (size_t i = 0; i < 16; i++){
            for (size_t j = 0; j < 16; j++){
                SDL_Rect destRect = { static_cast<int>(j * 32), static_cast<int>(i * 32), 32, 32 };
                if( mapa[i][j] == 0){
                    SDL_RenderCopy(renderer, tiles_stone ,nullptr, &destRect);
                }else{
                    SDL_RenderCopy(renderer, tiles_wall,nullptr, &destRect);
                }
            }
            
        }
        
        SDL_RenderPresent(renderer);  // Muestra en pantalla el contenido renderizado

        SDL_Delay(16); // Espera aprox. 16ms para lograr ~60 FPS
    }
    SDL_FreeSurface(stoneSurface);
    SDL_FreeSurface(wallSurface);

}


MapView::~MapView(){
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);  // Libera la textura
    if (renderer) SDL_DestroyRenderer(renderer);                  // Libera el renderer
    if (ventana) SDL_DestroyWindow(ventana);                      // Libera la ventana
    SDL_Quit();                                                   // Cierra SDL

}