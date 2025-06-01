#include "gameView.h"

GameView::GameView(Socket&& skt):
        config(),
        controller(std::move(skt)),
        leyenda(),
        ids(),
        ventana(),
        renderer(),
        backgroundTexture(),
        player(nullptr),
        camera(config.get_window_width() ,config.get_window_height()),
        manger_texture(),
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

    ventana = SDL_CreateWindow("Mapa", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,config.get_window_width() ,config.get_window_height(), SDL_WINDOW_SHOWN);
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


    for (PlayerImage& player_img : this->snapshot.players_images) {
        player_id_t id = player_img.player_id;

        if (id == snapshot.client_id) {

            std::cout << "Este es el jugador cliente. Guardando posición.\n";
            player->setCol(player_img.position.x); //
            player->setFil(player_img.position.y);

        }else if (players.find(id) == players.end()) {
            float x = player_img.position.x;
            float y = player_img.position.y;

            std::cout << "Nuevo jugador detectado. Creando PlayerView en (" << x << ", " << y << ")\n";

            PlayerView* nuevo_jugador = new PlayerView(x, y, "assets/gfx/terrorist/t2.png", 2.5f, &camera, &manger_texture,config);
            players[id] = nuevo_jugador;
        }else{
            std::cout << "actualizo pos de otro jugador\n";
            PlayerView* player_aux = players.at(id);  
            player_aux->setCol(player_img.position.x);
            player_aux->setFil(player_img.position.y);
        }
    }

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
    this->player = new PlayerView(x, y, img, speed, &camera, &manger_texture,config);
    return true;
}


void GameView::draw_game() {


    MapView map( "assets/pueblito_azteca.txt", &camera, &manger_texture,config);

    bool corriendo = true;
    SDL_Event evento;
    while (corriendo) {
        while (SDL_PollEvent(&evento)) {
            corriendo = handle_events(evento);
        }
        if(controller.has_game_image(this->snapshot)){
            update_status_game();
        }
        camera.update(player->getFil(),player->getCol(),player->getWidthImg(),player->getHeightImg(),map.getMapWidth(),map.getMapHeight());

        map.draw(*renderer); 
        player->draw(*renderer);
        draw_players();
        SDL_RenderPresent(renderer);

        SDL_Delay(16);  // Espera aprox. 16ms para lograr ~60 FPS
        SDL_RenderClear(renderer);
        
    }
    this->controller.stop();
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

}