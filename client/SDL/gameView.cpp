#include "gameView.h"
int counter2 = 0;
GameView::GameView(
        Socket&& skt):  // Aca realmente deberia de recibir el mapa y las armas disponibles, ya que
                        // es informacion necesaria para cargar el mapa
        config(),
        controller(std::move(skt)),
        leyenda(),
        texts(),
        ids(),
        ventana(init_window(config)),
        renderer(init_renderer(ventana, config)),
        backgroundTexture(nullptr),
        player(nullptr),
        camera(config.get_window_width(), config.get_window_height()),
        manger_texture(renderer),
        players(),
        snapshot(),
        map(nullptr),
        lastTime(SDL_GetTicks()),
        fov(nullptr),
        shop(camera, manger_texture, config),
        bomba(nullptr),
        hud(config, manger_texture),
        activa(false) {

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

SDL_Window* GameView::init_window(const GameConfig& config) {
    SDL_Window* window_game = SDL_CreateWindow(
            "Mapa", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config.get_window_width(),
            config.get_window_height(), SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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


bool GameView::init_game() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("Error al inicializar SDL: ") + SDL_GetError());
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        throw std::runtime_error(std::string("Error inicializando SDL_image: ") + IMG_GetError());
        return false;
    }

    try {
        load_textures();
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
        manger_texture.load(ids.at(par.first), par.second);
    }
}

void GameView::reset_values(PlayerView* player, const float& x_pixeles, const float& y_pixeles) {

    player->setPrevPos(player->getXActual(), player->getYActual());
    player->setTargetPos(x_pixeles, y_pixeles);
    player->setInterpTime(0.0f);
    player->setInterpDuration(0.1f);
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
            // player->update_weapons(snapshot.players_images[id].weapons);

        } else if (players.find(id) == players.end()) {
            Claves_skins claves;
            claves.ct_skin = player_img.skin.ct_skin;
            claves.tt_skin = player_img.skin.tt_skin;

            PlayerView* nuevo_jugador = new PlayerView(x_pixeles, y_pixeles, claves, 200.0f,
                                                       &camera, &manger_texture, config);
            nuevo_jugador->update_view_angle(player_img.mouse_position.x * 32,
                                             player_img.mouse_position.y * 32);
            // nuevo_jugador->update_weapons(snapshot.players_images[id].weapons);
            players[id] = nuevo_jugador;

        } else {
            PlayerView* player_aux = players.at(id);
            int x_pixel_mouse = player_img.mouse_position.x * config.get_tile_width();
            int y_pixel_mouse = player_img.mouse_position.y * config.get_tile_height();
            player_aux->update_view_angle(x_pixel_mouse, y_pixel_mouse);
            reset_values(player_aux, x_pixeles, y_pixeles);
            // player_aux->update_weapons(snapshot.players_images[id].weapons);
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
void GameView::handle_equip_type(const SDL_Keycode& tecla) {
    switch (tecla) {
        case SDLK_1:
            std::cout << "Presionaste la tecla 1" << std::endl;
            controller.sender_equip(EquipType::PRIMARY);
            break;
        case SDLK_2:
            controller.sender_equip(EquipType::SECONDARY);
            std::cout << "Presionaste la tecla 2" << std::endl;
            break;
        case SDLK_3:
            controller.sender_equip(EquipType::KNIFE);
            std::cout << "Presionaste la tecla 3" << std::endl;
            break;
        case SDLK_4:
            controller.sender_equip(EquipType::BOMB);
            std::cout << "Presionaste la tecla 4" << std::endl;
            break;
    }
}
void GameView::handle_movements(SDL_Keycode& tecla) {
    if (tecla == SDLK_w || tecla == SDLK_UP)
        controller.sender_move(MoveType::DOWN);
    if (tecla == SDLK_s || tecla == SDLK_DOWN)
        controller.sender_move(MoveType::UP);
    if (tecla == SDLK_a || tecla == SDLK_LEFT)
        controller.sender_move(MoveType::LEFT);
    if (tecla == SDLK_d || tecla == SDLK_RIGHT)
        controller.sender_move(MoveType::RIGHT);
    player->add_speed(tecla);
}
void GameView::handle_extras(SDL_Keycode& tecla) {
    if (tecla == SDLK_g)
        controller.sender_drop();
    if (tecla == SDLK_r)
        controller.sender_reload();
    if (tecla == SDLK_e)
        controller.sender_defuse();
}
void GameView::handle_key_down(SDL_Keycode& tecla) {
    if (snapshot.game_state.state != GameState::TIME_TO_BUY)
        shop.desactivate_shop();
    if (tecla == SDLK_b && snapshot.game_state.state == GameState::TIME_TO_BUY) {
        shop.activate_shop();
    }
    handle_movements(tecla);
    handle_equip_type(tecla);
    handle_extras(tecla);
}
void GameView::handle_mouse_left_down(int mouseX, int mouseY) {
    if (shop.get_activa()) {
        WeaponCode code = shop.calculate_selection(mouseX, mouseY);
        // Realmente esto no deberia de siquiera pasar, casi que es una exception
        if (code != WeaponCode::NONE)
            controller.sender_buy_weapon(code);
    }
    if (snapshot.game_state.state == GameState::ROUND_STARTED)
        controller.sender_shoot(mouseX, mouseY);
}
void GameView::handle_events(const SDL_Event& event) {
    try {
        if (event.type == SDL_QUIT) {
            this->controller.stop();
            throw QuitGameException("Juego cerrado por el usuario");
        }

        if (event.type == SDL_KEYDOWN) {
            SDL_Keycode tecla = event.key.keysym.sym;
            handle_key_down(tecla);
        }
        if (event.type == SDL_KEYUP) {
            SDL_Keycode tecla = event.key.keysym.sym;
            player->stop_speed(tecla);  // Detiene movimiento
        }
        if (event.type == SDL_WINDOWEVENT) {  // LA PANTALLA
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                this->map->update_map_dimensions();
                printf("Nuevo mapa width: %d, height: %d\n", map->getMapWidth(),
                       map->getMapHeight());
            }
        }

        if (event.type == SDL_MOUSEMOTION) {  // para mover mouse
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;
            player->update_view_angle(mouseX, mouseY);
            controller.sender_pos_mouse(mouseX, mouseY);
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                handle_mouse_left_down(mouseX, mouseY);
            }
        }

    } catch (const ClosedQueue&
                     e) {  // Si la cola se cierra, significa que el servidor se ha cerrado
        this->controller.stop();
    }
}


bool GameView::add_player(float x, float y, int speed, const Claves_skins& claves) {
    this->player = new PlayerView(x, y, claves, speed, &camera, &manger_texture, config);
    return true;
}


void GameView::initial_draw_game(const GameInfo& info_game_view /*,const Player& info_game*/) {

    this->map = new MapView(info_game_view.map_info.walls, &camera, &manger_texture, config);
    if (!map) {
        throw std::runtime_error("Error al cargar mapa");
        return;
    }
    this->fov = new FieldOfView(*player, camera, manger_texture, config);
    shop.set_weapons_purchasables(info_game_view.weapons_purchasables);
}

void GameView::process_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        this->handle_events(event);
    }
}

void GameView::update_game_state(float deltaTime) {
    try {
        if (controller.has_game_image(this->snapshot)) {
            bool found = false;
            player_id_t counter = 0;
            player_id_t index_player_id = 0;

            while (!found && counter < snapshot.players_images.size()) {
                if (snapshot.players_images[counter].player_id == snapshot.client_id) {
                    index_player_id = counter;
                    found = true;
                }
                counter++;
            }
            if (found) {
                hud.load(snapshot.players_images[index_player_id], snapshot.bomb,
                         snapshot.game_state.time, snapshot.game_state);
            } else {
                std::cerr << "Error: No se encontró el jugador con client_id " << snapshot.client_id
                          << " en players_images\n";
            }
        }
    } catch (const ClosedQueue& e) {  // comportamiento esperado
        this->controller.stop();
    }

    update_status_game();
    player->update(deltaTime);

    for (auto& pair: players) {
        if (pair.second != nullptr && pair.second != player) {
            pair.second->update(deltaTime);
        }
    }
    camera.update(player->getYActual(), player->getXActual(), player->getWidthImg(),
                  player->getHeightImg(), map->getMapWidth(), map->getMapHeight());
}


void GameView::render_game() {
    SDL_RenderClear(renderer);

    map->draw(*renderer);
    player->draw(*renderer);
    draw_players();
    // if (bomba)
    //    bomba->draw(*renderer);
    fov->draw(*renderer);
    if (shop.get_activa()) {
        shop.draw(*renderer);
    }
    hud.render(*renderer);
    SDL_RenderPresent(renderer);
}

void GameView::draw_game() {
    bomba = new Bomb(0, 0, camera, manger_texture, config);

    auto keep_running = [&]() -> bool {
        process_events();
        return true;
    };

    auto game_step = [&]() {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        update_game_state(deltaTime);
        render_game();
    };

    ConstantRateLoop loop(keep_running, game_step);
    loop.execute();
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


    if (fov)
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
