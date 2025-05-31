#include "gameView.h"


#define MAPA_AZTECA "assets/pueblito_azteca.txt"

GameView::GameView(Socket&& skt, const int& width_reseiver, const int& height_reseiver):
        controller(std::move(skt)),
        leyenda(),
        ids(),
        ventana(),
        renderer(),
        backgroundTexture(),
        player(nullptr),
        camera({0, 0, width_reseiver, height_reseiver}),
        manger_texture(),
        width(width_reseiver),
        height(height_reseiver) {
    leyenda['#'] = "assets/gfx/backgrounds/nuke.png";
    leyenda[' '] = "assets/gfx/backgrounds/stone1.jpg";
    leyenda['~'] = "assets/gfx/backgrounds/water4.jpg";
    leyenda['='] = "assets/gfx/box.PNG";
    leyenda['.'] = "assets/gfx/backgrounds/gras1.jpg";

    ids['#'] = Objet::WALL;
    ids[' '] = Objet::STONE;
    ids['~'] = Objet::WATER;
    ids['='] = Objet::BOX;
    ids['.'] = Objet::GRASS;
}


void GameView::load_textures() {
    for (const auto& par: leyenda) {
        manger_texture.load(ids.at(par.first), par.second, renderer);
    }
}


bool GameView::handle_events(const SDL_Event& evento) {

    if (evento.type == SDL_QUIT) {
        return false;  // Se cierra la ventana
    } else if (evento.type == SDL_KEYDOWN) {

        SDL_Keycode tecla = evento.key.keysym.sym;  // Se presionó una tecla
        controller.sender_mov_player(tecla);
        Position pos = controller.recibir();
        player->setCol(pos.x);
        player->setFil(pos.y);
        // player->add_speed(tecla);
    } else if (evento.type == SDL_MOUSEMOTION) {

        int mouseX = evento.motion.x;
        int mouseY = evento.motion.y;
        player->update_view_angle(mouseX, mouseY);
        controller.sender_pos_mouse(mouseX, mouseY);
    }
    return true;
}

/*bool GameView::cargarTexturaFondo(SDL_Renderer* renderer) {

    SDL_Surface* surface = SDL_LoadBMP("assets/gfx/tiles/default_aztec.bmp"); // Carga la imagen BMP
desde la ruta dada a una superficie if (!surface) { std::cerr << "Error cargando imagen: " <<
SDL_GetError() << std::endl; return false;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);  // Convierte la superficie
a una textura que se puede usar para renderizar SDL_FreeSurface(surface);

    if (!backgroundTexture) {
        std::cerr << "Error creando textura: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}
*/

void GameView::add_player(PlayerView& player_aux) { player = &player_aux; }


std::vector<std::vector<char>> GameView::cargar_mapa(const std::string& archivo) {

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
    return mapa;
}

bool GameView::init_render_window() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {  // Inicializa SDL con soporte para video
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    ventana = SDL_CreateWindow("Mapa", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,
                               height, SDL_WINDOW_SHOWN);
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
    // if (!cargarTexturaFondo(renderer)) {
    //   return false;
    //}
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        std::cerr << "Error inicializando SDL_image: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}


void GameView::draw_game() {

    if (!init_render_window()) {
        throw std::runtime_error("No se pudo inicializar el juego visual");
        return;
    }
    //------------------cargo texturas------------
    load_textures();
    if (!manger_texture.load(Objet::PLAYER, "assets/gfx/terrorist/t1_1.png", renderer)) {
        std::cerr << "Error: No se pudo cargar la textura del jugador." << std::endl;
    }
    //--------------inicializo clases----------------
    const float speed = 2.5f;
    float x = 0;
    float y = 0;
    PlayerView player(x, y, "assets/gfx/terrorist/t1_1.png", speed, &camera, &manger_texture);
    add_player(player);

    //------------juego----------------------------

    std::vector<std::vector<char>> mapa = cargar_mapa(MAPA_AZTECA);
    MapView map(mapa, 500, 500, &camera, &manger_texture);

    bool corriendo = true;
    SDL_Event evento;
    while (corriendo) {
        while (SDL_PollEvent(&evento)) {
            corriendo = handle_events(evento);
        }
        SDL_RenderClear(renderer);

        //---------------------------------------------------------------------------
        //  Actualiza la cámara para que siga al jugador
        camera.x = player.getCol() + player.getWidthImg() / 2 - camera.w / 2;
        camera.y = player.getFil() + player.getHeightImg() / 2 - camera.h / 2;

        // calcular la camara
        if (camera.x < 0)
            camera.x = 0;
        if (camera.y < 0)
            camera.y = 0;
        if (camera.x > map.getMapWidth() - camera.w)
            camera.x = map.getMapWidth() - camera.w;
        if (camera.y > map.getMapHeight() - camera.h)
            camera.y = map.getMapHeight() - camera.h;
        //------------------------------------------------------------------------------------
        // ... dibujá cosas ...-----------------------
        map.draw(*renderer);  // completar mapa
        player.draw(*renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16);  // Espera aprox. 16ms para lograr ~60 FPS
    }
}

GameView::~GameView() {
    if (backgroundTexture)
        SDL_DestroyTexture(backgroundTexture);  // Libera la textura
    if (renderer)
        SDL_DestroyRenderer(renderer);  // Libera el renderer
    if (ventana)
        SDL_DestroyWindow(ventana);  // Libera la ventana
    SDL_Quit();                      // Cierra SDL
    IMG_Quit();
    this->controller.stop();
}
