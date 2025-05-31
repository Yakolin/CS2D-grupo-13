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
        camera(width_reseiver,height_reseiver),
        manger_texture(),
        width(width_reseiver),
        height(height_reseiver) ,
        players(),
        snapshot()
        {
    leyenda['#'] = "assets/gfx/backgrounds/nuke.png";
    leyenda[' '] = "assets/gfx/backgrounds/stone1.jpg";
    leyenda['~'] = "assets/gfx/backgrounds/water4.jpg";
    leyenda['='] = "assets/gfx/box.PNG";
    leyenda['.'] = "assets/gfx/backgrounds/gras1.jpg";

    ids['#'] = Object::WALL;
    ids[' '] = Object::STONE;
    ids['~'] = Object::WATER;
    ids['='] = Object::BOX;
    ids['.'] = Object::GRASS;
    
}
bool GameView::cargar_skins(const std::map<Object, std::string >& rutas_skins) {
    
    for (const auto& par : rutas_skins) {
        
        if (!this->manger_texture.load(par.first, par.second, renderer)) {
            std::cerr << "Fallo al cargar la textura para skin: " << std::endl;
            return false;
        }
    }
    return true;
}

bool GameView::init_game() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { 
        throw std::runtime_error(std::string("Error al inicializar SDL: ") + SDL_GetError());
        return false;
    }

    ventana = SDL_CreateWindow("Mapa", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,height, SDL_WINDOW_SHOWN);
    if (!ventana) {
        throw std::runtime_error(std::string("Error al crear la ventana: ") + SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        throw std::runtime_error(std::string("Error al crear el renderer: ") + SDL_GetError());
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        throw std::runtime_error(std::string("Error inicializando SDL_image: ") + IMG_GetError());
        return false;
    }

    load_textures();
    return true;
}

void GameView::load_textures() {
    for (const auto& par: leyenda) {
        manger_texture.load(ids.at(par.first), par.second, renderer);
    }
}

void GameView::update_status_game() {
    PlayerImage actual(0, Position{0, 0}, 0, 0); 

    for (PlayerImage& player_img : this->snapshot.players_images) {
        player_id_t id = player_img.player_id;

        std::cout << "Procesando jugador ID: " << id << "\n";
        std::cout << "Posición actual del jugador: (" << player_img.position.x << ", " << player_img.position.y << ")\n";

        if (id == snapshot.client_id) {
            actual = player_img;
            std::cout << "Este es el jugador cliente. Guardando posición.\n";

        }else if (players.find(id) == players.end()) {
            float x = player_img.position.x;
            float y = player_img.position.y;

            std::cout << "Nuevo jugador detectado. Creando PlayerView en (" << x << ", " << y << ")\n";

            PlayerView* nuevo_jugador = new PlayerView(x, y, "assets/gfx/terrorist/t1_1.png", 5.0f, &camera, &manger_texture);
            players[id] = nuevo_jugador;
        }
    }

    // Antes de actualizar el jugador, imprimir valores que vas a asignar
    std::cout << "Actualizando jugador cliente:\n";
    std::cout << "Col anterior: " << player->getCol() << " Fil anterior: " << player->getFil() << "\n";

    player->setCol(actual.position.x); //
    player->setFil(actual.position.y);


    std::cout << "Col nueva: " << player->getCol() << " Fil nueva: " << player->getFil() << "\n";

}


void GameView::draw_players(){

    for (auto& pair : this->players) {
        PlayerView* player = pair.second;
        if (player) {
            player->draw(*renderer);
        }
    }
}


bool GameView::handle_events(const SDL_Event& evento) {

    if (evento.type == SDL_QUIT) {
        return false;  
    } else if (evento.type == SDL_KEYDOWN) {

        SDL_Keycode tecla = evento.key.keysym.sym;  // Se presionó una tecla
        controller.sender_mov_player(tecla);
        controller.recibir(this->snapshot);
        update_status_game();
        //player->add_speed(tecla);
        return true;
    } else if (evento.type == SDL_MOUSEMOTION) {

        int mouseX = evento.motion.x;
        int mouseY = evento.motion.y;
        player->update_view_angle(mouseX, mouseY);
        //controller.sender_pos_mouse(mouseX, mouseY);
        return true;
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

bool GameView::add_player(float x, float y ,int speed, const std::string& img ) { 

    if (!manger_texture.load(Object::PLAYER, img, renderer)) {
        std::cerr << "Error: No se pudo cargar la textura del jugador." << std::endl;
        return false;
    }
    this->player = new PlayerView(x, y, img, speed, &camera, &manger_texture);
    return true;
}

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


void GameView::draw_game() {


    std::vector<std::vector<char>> mapa = cargar_mapa(MAPA_AZTECA);
    MapView map(mapa, 500, 500, &camera, &manger_texture);

    bool corriendo = true;
    SDL_Event evento;
    while (corriendo) {
        while (SDL_PollEvent(&evento)) {
            corriendo = handle_events(evento);
        }
        SDL_RenderClear(renderer);
        camera.update(player->getFil(),player->getCol(),player->getWidthImg(),player->getHeightImg(),map.getMapWidth(),map.getMapHeight());

        map.draw(*renderer); 
        player->draw(*renderer);
        draw_players();
        SDL_RenderPresent(renderer);

        SDL_Delay(16);  // Espera aprox. 16ms para lograr ~60 FPS
    }
}

GameView::~GameView() {
    this->manger_texture.clear();
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