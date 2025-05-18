#include "mapView.h"
MapView::MapView( const std::vector<std::vector<char>>& mapa_recibido, 
                    const int& width_reseiver , const int& height_reseiver) :
    backgroundTexture(),
    ventana(),
    renderer(),
    leyenda(),
    width(width_reseiver) ,
    height(height_reseiver),
    mapa(mapa_recibido),
    texturas(),
    player(nullptr),
    width_map(mapa_recibido[0].size() * 32),
    height_map(mapa_recibido.size() * 32),
    camera({0, 0, width_reseiver,height_reseiver})
{
    leyenda['#'] = "../assets/gfx/backgrounds/nuke.png";
    leyenda[' '] = "../assets/gfx/backgrounds/stone1.jpg";
    leyenda['~'] = "../assets/gfx/backgrounds/water4.jpg";
    leyenda['='] = "../assets/gfx/box.PNG";
    leyenda['.'] = "../assets/gfx/backgrounds/gras1.jpg";

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
            SDL_Rect destRect = { 
                static_cast<int>(j * 32) - camera.x , 
                static_cast<int>(i * 32) - camera.y, 
                32, 32 };

            char item = mapa[i][j];
            SDL_Texture* tex = texturas[item];
            if (tex)
                SDL_RenderCopy(renderer, tex, nullptr, &destRect);
        }
    }

}

bool MapView::init_game(){

    if(!initialize_sdl_video() || !init_render_window()){
        return false;
    }
    return true;
}

void MapView::add_player(PlayerView& player_aux){

    player = &player_aux;
}

bool MapView::handle_events(const SDL_Event& evento){
    if (evento.type == SDL_QUIT){ 
        return false;  // Se cierra la ventana
    }else if(evento.type == SDL_KEYDOWN) {
        SDL_Keycode tecla = evento.key.keysym.sym; // Se presionó una tecla
        player->add_speed(tecla);
    }else if (evento.type == SDL_MOUSEMOTION) {
        int mouseX = evento.motion.x;
        int mouseY = evento.motion.y;
        player->update_view_angle(mouseX,mouseY);
        // std::cout << "Mouse en: " << mouseX << ", " << mouseY << std::endl;
    }
    return true;
}

void MapView::show_map() {

    bool corriendo = true;
    SDL_Event evento;
    load_textures();

    int ancho=0;
    int alto=0;
    SDL_Texture* tiles_player = add_tiles(player->getRutaPlayer());
    SDL_QueryTexture(tiles_player, nullptr, nullptr, &ancho, &alto);
    std::cout << "Ancho: " << ancho << ", Alto: " << alto << std::endl;
    MedidasSprites sprite;
    sprite.height =alto;
    sprite.width =ancho;

    while (corriendo) {
        while (SDL_PollEvent(&evento)) {
            corriendo = handle_events(evento);
        }
        SDL_RenderClear(renderer);  // Limpia el render anterio
//---------------------------------------------------------------------------
       //  Actualiza la cámara para que siga al jugador
        camera.x = player->getCol() + sprite.width/2 - camera.w/2;
        camera.y = player->getFil() + sprite.height/2 - camera.h/2;

        // Limita la cámara para que no se salga del mapa
        if (camera.x < 0) camera.x = 0;
        if (camera.y < 0) camera.y = 0;
        if (camera.x > width_map - camera.w) camera.x = width_map - camera.w;
        if (camera.y > height_map - camera.h) camera.y = height_map - camera.h;

//------------------------------------------------------------------------------------
        complete_map_view(); // completar mapa
     //   std::string posText = "Fil: " + std::to_string(player->getFil()) + " Col: " + std::to_string(player->getCol());
        player->draw_player(renderer,tiles_player,sprite, camera);
        
        SDL_RenderPresent(renderer);  // Muestra en pantalla el contenido renderizado
        SDL_Delay(16); // Espera aprox. 16ms para lograr ~60 FPS
    }
    if (tiles_player) SDL_DestroyTexture(tiles_player);

}


MapView::~MapView(){
    IMG_Quit();
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);  // Libera la textura
    if (renderer) SDL_DestroyRenderer(renderer);                  // Libera el renderer
    if (ventana) SDL_DestroyWindow(ventana);                      // Libera la ventana
    for (auto& par : texturas) {
        if (par.second) SDL_DestroyTexture(par.second);
    }
    SDL_Quit();                                                   // Cierra SDL

}
