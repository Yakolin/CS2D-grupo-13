#include "gameView.h"

GameView::GameView(Socket&& skt):
        config(),
        controller(std::move(skt)),
        leyenda(),
        texts(),
        ids(),
        ventana(init_window(config)),
        renderer(init_renderer(ventana,config)),
        backgroundTexture(nullptr),
        player(nullptr),
        camera(config.get_window_width(), config.get_window_height()),
        manger_texture(renderer),
        players(),
        snapshot(),
        map(nullptr),
        text(nullptr),
        lastTime(SDL_GetTicks()) , 
        fov(nullptr),
        bomb_activate(false)
{
    texts = {{TextView::VIDA, "Vida : 0 "},
             {TextView::PUNTOS, "Puntos : 0"},
             {TextView::MUERTES, "Muertes: 0"},
             {TextView::RONDA, "Ronda n°: 1"}};

    leyenda['#'] = "assets/gfx/backgrounds/nuke.png";
    leyenda[' '] = "assets/gfx/backgrounds/stone1.jpg";
    leyenda['~'] = "assets/gfx/backgrounds/water4.jpg";
    leyenda['='] = "assets/gfx/box.PNG";
    leyenda['.'] = "assets/gfx/backgrounds/gras1.jpg";
    leyenda['A'] = "assets/gfx/backgrounds/zonaa.jpeg";
    leyenda['B'] = "assets/gfx/backgrounds/zonab.jpeg";
    leyenda['C'] = "assets/gfx/backgrounds/zonacounter.jpeg";
    leyenda['T'] = "assets/gfx/backgrounds/zonaTerrorist.jpeg";

    ids['#'] = Object::WALL;
    ids[' '] = Object::STONE;
    ids['~'] = Object::WATER;
    ids['='] = Object::BOX;
    ids['.'] = Object::GRASS;
    ids['A'] = Object::ZONE_BOMBA2;
    ids['B'] = Object::ZONE_BOMBA1;
    ids['T'] = Object::ZONE_TERRORIST;
    ids['C'] = Object::ZONE_COUNTERTERROSIT;
}

SDL_Window* GameView::init_window(const GameConfig& config){
    SDL_Window*  window_game = SDL_CreateWindow("Mapa", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                config.get_window_width(), config.get_window_height(),
                                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window_game) {
        throw std::runtime_error(std::string("Error al crear la window_game: ") + SDL_GetError());
    }
    return window_game;
}

SDL_Renderer* GameView::init_renderer(SDL_Window* window, GameConfig& config) {

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        throw std::runtime_error(std::string("Error al crear el renderer: ") + SDL_GetError());
    }
    SDL_RenderSetLogicalSize(renderer, config.get_viewpost_width(), config.get_viewpost_height());
    return renderer;
}

bool GameView::cargar_skins(const std::map<Object, std::string>& rutas_skins) {
    for (const auto& par: rutas_skins) {
        if (!this->manger_texture.load(par.first, par.second, renderer)) {
            std::cerr << "Fallo al cargar la textura para skin: " << std::endl;
            return false;
        }
    }
    return true;
}

bool GameView::load_text() {
    TTF_Font* fuente = TTF_OpenFont(config.get_font().c_str(), 23);
    if (!fuente) {
        std::cerr << "Error al abrir fuente: " << TTF_GetError() << std::endl;
        return false;
    }

    SDL_Color color = config.get_blanco();

    for (const auto& par: texts) {
        if (!this->manger_texture.load_texture_text(par.first, fuente, color, par.second,
                                                    renderer)) {
            std::cerr << "Fallo al cargar la textura de texto : " << std::endl;
            TTF_CloseFont(fuente);
            return false;
        }
    }

    TTF_CloseFont(fuente);
    return true;
}

bool GameView::init_game() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("Error al inicializar SDL: ") + SDL_GetError());
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        throw std::runtime_error(std::string("Error inicializando SDL_image: ") + IMG_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        SDL_Log("Error al inicializar SDL_ttf: %s", TTF_GetError());
        return false;
    }

    try {
        load_textures();
        load_text();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return false;
    } catch (...) {
        std::cerr << "Excepción desconocida en load_text o load_textures" << std::endl;
        return false;
    }

    return true;
}

void GameView::load_textures() {
    for (const auto& par: leyenda) {
        manger_texture.load(ids.at(par.first), par.second, renderer);
    }
}

bool GameView::load_weapon(const std::map<Weapon, std::string>& route_weapons) {

    for (const auto& par: route_weapons) {
        if (!this->manger_texture.load_weapons(par.first, par.second, renderer)) {
            std::cerr << "Fallo al cargar la textura del arma: " << std::endl;
            return false;
        }
    }
    return true;
}
void GameView::reset_values(PlayerView* player, const float& x_pixeles, const float& y_pixeles) {

    player->setPrevPos(player->getXActual(), player->getYActual());
    player->setTargetPos(x_pixeles, y_pixeles);
    player->setInterpTime(0.0f);
    player->setInterpDuration(0.1f);

    player->setCol(x_pixeles);
    player->setFil(y_pixeles);
}
void GameView::update_status_game() {

    int tile_width = config.get_tile_width();
    int tile_height = config.get_tile_height();

    for (PlayerImage& player_img: this->snapshot.players_images) {
        player_id_t id = player_img.player_id;

        float x_pixeles = player_img.position.x * tile_width;
        float y_pixeles = player_img.position.y * tile_height;

        if (id == snapshot.client_id) {
            reset_values(player, x_pixeles, y_pixeles);

        } else if (players.find(id) == players.end()) {
            PlayerView* nuevo_jugador =
                    new PlayerView(x_pixeles, y_pixeles, "assets/gfx/terrorist/t2.png", 200.0f,&camera, &manger_texture, config);
                    nuevo_jugador->update_view_angle(player_img.mouse_position.x*32,player_img.mouse_position.y*32);
                    players[id] = nuevo_jugador;
        } else {
            PlayerView* player_aux = players.at(id);
            int x_pixel_mouse = player_img.mouse_position.x * config.get_tile_width();
            int y_pixel_mouse = player_img.mouse_position.y * config.get_tile_height();
            printf("pos mouse recibida (%d, %d)\n",x_pixel_mouse, y_pixel_mouse);
            player_aux->update_view_angle(x_pixel_mouse,y_pixel_mouse);
            reset_values(player_aux, x_pixeles, y_pixeles);
        }
    }
}

void GameView::draw_players() {
    for (auto& pair: this->players) {
        PlayerView* player = pair.second;
        if (player) {

            player->draw(*renderer);
        }
    }
}
bool GameView::handle_events(const SDL_Event& event) {
    if (event.type == SDL_QUIT) {
        return false;

    } else if (event.type == SDL_KEYDOWN) {
        SDL_Keycode tecla = event.key.keysym.sym;
        controller.sender_mov_player(tecla); 
        if (event.key.keysym.sym == SDLK_5) {
            // El jugador presionó la tecla 5
            std::cout << "Tecla 5 presionada" << std::endl;
            return true;
            // Aquí podés activar la bomba o cualquier otra acción
        }
        player->add_speed(tecla);

        return true;

    } else if (event.type == SDL_KEYUP) {
        SDL_Keycode tecla = event.key.keysym.sym;
        player->stop_speed(tecla);  // Detiene movimiento
        return true;
    } else if (event.type == SDL_WINDOWEVENT) {
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {

            this->map->update_map_dimensions();
            printf("Nuevo mapa width: %d, height: %d\n", map->getMapWidth(), map->getMapHeight());
        }
    } if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            player->activate_weapon(Weapon::AK47);  
            printf("Clic izquierdo detectado en (%d, %d)\n",event.button.x, event.button.y);
        }
    }
    if (event.type == SDL_MOUSEMOTION) {
        int mouseX = event.motion.x;
        int mouseY = event.motion.y;
        player->update_view_angle(mouseX, mouseY);
        printf("-----------mov mouse----------------------\n");
        printf("MOUSER en (%d, %d)\n",mouseX, mouseY);

        controller.sender_pos_mouse(mouseX, mouseY);
        
        
        return true;
    }

    return true;
}


bool GameView::add_player(float x, float y, int speed, const std::string& img) {
    if (!manger_texture.load(Object::PLAYER, img, renderer)) {
        std::cerr << "Error: No se pudo cargar la textura del jugador." << std::endl;
        return false;
    }  
    this->player = new PlayerView(x, y, img, speed, &camera, &manger_texture, config);
    return true;
}

void GameView::draw_game(const std::vector<Position> walls) {

    this->map = new MapView(walls,&camera, &manger_texture, config);
    if (!map) {
        throw std::runtime_error("Error al cargar mapa");
        return;
    }
    this->fov = new FieldOfView(*player,camera,manger_texture,config);

    text = new Text(&manger_texture, TextView::VIDA, 10, 10);
    SDL_Event event;

   // Bomb bomba = Bomb(player,camera,manger_texture,config);

    auto keep_running = [&]() -> bool {
        while (SDL_PollEvent(&event)) {
            if (!handle_events(event)) {
                return false;
            }
        }
        return true;
    };

    auto game_step = [&]() {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        if (controller.has_game_image(this->snapshot)) {
            update_status_game();
        }
        player->update(deltaTime);

        for (auto& pair: players) {
            if (pair.second != nullptr && pair.second != player) {
                pair.second->update(deltaTime);
            }
        }
        camera.update(player->getYActual(), player->getXActual(), player->getWidthImg(),
                      player->getHeightImg(), map->getMapWidth(), map->getMapHeight());

        // Render
        SDL_RenderClear(renderer);

        map->draw(*renderer);
        player->draw(*renderer);
        draw_players();
        text->draw(*renderer);
        fov->draw(*renderer);
        //if(bomb_activate){
        //    bomba.draw(*renderer);
        //}

        SDL_RenderPresent(renderer);
    };

    ConstantRateLoop loop(keep_running, game_step);
    loop.execute();

    //-----------------------------------------------------------
    try {
        this->controller.stop();
    } catch (const std::exception& e) {
        std::cerr << "Excepción deteniendo a los hilos: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Excepción desconocida en stop" << std::endl;
    }
}

GameView::~GameView() {
    for (auto& p: players) {
        delete p.second;
    }
    players.clear();

    delete player;
    player = nullptr;

    if (map)
        delete map;

    if (text)
        delete text;
    if(fov)
        delete fov;

    this->manger_texture.clear();

    if (backgroundTexture)
        SDL_DestroyTexture(backgroundTexture);

    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (ventana)
        SDL_DestroyWindow(ventana);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
