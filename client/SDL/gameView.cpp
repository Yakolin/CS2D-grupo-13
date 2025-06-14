#include "gameView.h"
int counter2 = 0;
GameView::GameView(
        Socket&& skt):  // Aca realmente deberia de recibir el mapa y las armas disponibles, ya que
                        // es informacion necesaria para cargar el mapa
        config(),
        controller(std::move(skt)),
        texts(),
        ventana(init_window(config)),
        renderer(init_renderer(ventana, config)),
        player(nullptr),
        camera(config.get_window_width(), config.get_window_height()),
        manger_texture(renderer),
        players(),
        snapshot(),
        map(nullptr),
        fov(nullptr),
        shop(camera, manger_texture, config),
        bomba(nullptr),
        hud(config, manger_texture),
        activa(false),
        bullets() {}

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

    return true;
}


void GameView::reset_values(PlayerView* player, const float& x_pixeles, const float& y_pixeles) {

    player->setPrevPos(player->getXActual(), player->getYActual());
    player->setTargetPos(x_pixeles, y_pixeles);
    player->setInterpTime(0.0f);
    // player->setInterpDuration(0.1f);
}

void print_game_image(const GameImage& image) {
    /*
    std::cout << "=== Game Image ===\n";
    std::cout << "Client ID: " << image.client_id << "\n";
    std::cout << "--- Players ---\n";
    for (const auto& player: image.players_images) {
        std::cout << "Player ID: " << player.player_id << "\n";
        std::cout << "  Position: (" << player.position.x << ", " << player.position.y << ")\n";
        std::cout << "  Health: " << static_cast<int>(player.health) << "\n";
        std::cout << "  Points: " << static_cast<int>(player.points) << "\n";
        std::cout << "  Money: " << player.money << "\n";
        std::cout << "  Equipped weapon: " << static_cast<int>(player.equipped_weapon) << "\n";
        std::cout << "  Mouse position: (" << player.mouse_position.x << ", "
                  << player.mouse_position.y << ")\n";
        std::cout << "  Team: " << (player.team == Team::CT ? "CT" : "TT") << "\n";
        std::cout << "  Weapons:\n";
        for (const auto& weapon: player.weapons) {
            std::cout << "    WeaponCode: " << static_cast<int>(weapon.weapon_code)
            << ", Current: " << static_cast<int>(weapon.current_bullets)
                      << ", Magazine: " << static_cast<int>(weapon.magazine)
                      << ", Inventory: " << static_cast<int>(weapon.inventory_bullets) << "\n";
        }
    }

    */
    std::cout << "--- Bullets in Air ---\n";
    for (const auto& bullet: image.bullets_in_air) {
        std::cout << "  From (" << bullet.initial.x << ", " << bullet.initial.y << ") to ("
                  << bullet.end.x << ", " << bullet.end.y << ")\n";
    }
    /*
    std::cout << "--- Bomb ---\n";
    std::cout << "  Position: (" << image.bomb.position.x << ", " << image.bomb.position.y << ")\n";
    std::cout << "  State: " << static_cast<int>(image.bomb.state) << "\n";

    std::cout << "--- Dropped Weapons ---\n";
    for (const auto& dropped: image.dropped_things) {
        std::cout << "  WeaponCode: " << static_cast<int>(dropped.weapon_code) << ", Position: ("
        << dropped.position.x << ", " << dropped.position.y << ")\n";
    }

    std::cout << "--- Game State ---\n";
    std::cout << "  State: " << static_cast<int>(image.game_state.state) << "\n";
    std::cout << "  Time: " << image.game_state.time << "\n";
    std::cout << "  Round: " << static_cast<int>(image.game_state.round) << "\n";
    */
}

void GameView::update_status_game() {
    print_game_image(snapshot);
    for (const BulletImage& bullet: snapshot.bullets_in_air) {
        std::cout << "Initial: (" << bullet.initial.x << ", " << bullet.initial.y << ")\n";
        std::cout << "End: (" << bullet.end.x << ", " << bullet.end.y << ")\n";
        Coordenada init = {static_cast<float>(bullet.initial.x),
                           static_cast<float>(bullet.initial.y)};
        Coordenada end = {static_cast<float>(bullet.end.x), static_cast<float>(bullet.end.y)};

        Bullet bullet_aux(init, end, manger_texture.get(Object::BULLET));
        this->bullets.push_back(bullet_aux);
    }

    int tile_width = config.get_tile_width();
    int tile_height = config.get_tile_height();

    for (PlayerImage& player_img: this->snapshot.players_images) {
        player_id_t id = player_img.player_id;

        float x_pixeles = player_img.position.x * tile_width;
        float y_pixeles = player_img.position.y * tile_height;

        if (id == snapshot.client_id) {
            reset_values(player, x_pixeles, y_pixeles);
            player->update_weapons(player_img.weapons);
            player->update_equip(player_img);

        } else if (players.find(id) == players.end()) {
            Claves_skins claves;
            claves.ct_skin = player_img.skin.ct_skin;
            claves.tt_skin = player_img.skin.tt_skin;

            PlayerView* nuevo_jugador = new PlayerView(x_pixeles, y_pixeles, claves, 200.0f,
                                                       &camera, &manger_texture, config);
            nuevo_jugador->update_view_angle(player_img.mouse_position.x * 32,
                                             player_img.mouse_position.y * 32);
            nuevo_jugador->update_weapons(player_img.weapons);
            players[id] = nuevo_jugador;

        } else {
            PlayerView* player_aux = players.at(id);
            int x_pixel_mouse = player_img.mouse_position.x * config.get_tile_width();
            int y_pixel_mouse = player_img.mouse_position.y * config.get_tile_height();
            player_aux->update_view_angle(x_pixel_mouse, y_pixel_mouse);
            reset_values(player_aux, x_pixeles, y_pixeles);
            player_aux->update_weapons(player_img.weapons);
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
            controller.sender_equip(EquipType::PRIMARY);
            break;
        case SDLK_2:
            controller.sender_equip(EquipType::SECONDARY);
            break;
        case SDLK_3:
            controller.sender_equip(EquipType::KNIFE);
            break;
        case SDLK_4:
            controller.sender_equip(EquipType::BOMB);
            break;
    }
}

void GameView::mouse_position_tiles(int& posx, int& posy, const int& mousex, const int& mousey) {
    const int TILE_SIZE = 32;

    int camX = camera.getX();
    int camY = camera.getY();
    int mapPixelX = mousex + camX;
    int mapPixelY = mousey + camY;

    posx = mapPixelX / TILE_SIZE;
    posy = mapPixelY / TILE_SIZE;

    if (posx >= 0 && posx < 50 && posy >= 0 && posy < 50) {
        printf("Estás sobre el tile (%d, %d)\n", posx, posy);
    } else {
        printf("El mouse está fuera del mapa.\n");
    }
}
bool GameView::handle_events(const SDL_Event& event) {
    if (event.type == SDL_QUIT) {
        return false;
    }

    if (event.type == SDL_KEYDOWN) {  // precionas una tecla
        SDL_Keycode tecla = event.key.keysym.sym;
        player->add_speed(tecla);
        controller.sender_mov_player(tecla);
        if (snapshot.game_state.state != GameState::TIME_TO_BUY)
            shop.desactivate_shop();
        if (tecla == SDLK_b && snapshot.game_state.state == GameState::TIME_TO_BUY) {
            shop.activate_shop();
        }
        handle_equip_type(tecla);
    }

    if (event.type == SDL_KEYUP) {  // sueeltas una teca
        SDL_Keycode tecla = event.key.keysym.sym;
        player->stop_speed(tecla);  // Detiene movimiento
        return true;
    }

    if (event.type == SDL_WINDOWEVENT) {
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
            this->map->update_map_dimensions();
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
            int mousex_tile = -1;
            int mousey_tile = -1;
            mouse_position_tiles(mousex_tile, mousey_tile, mouseX, mouseY);
            if (shop.get_activa()) {
                WeaponCode code = shop.calculate_selection(mouseX, mouseY);
                if (code != WeaponCode::NONE)  // Realmente esto no deberia de siquiera pasar, casi
                                               // que es una exception
                    controller.sender_buy_weapon(code);
            }
            if (snapshot.game_state.state == GameState::ROUND_STARTED) {
                controller.sender_shoot(mousex_tile, mousey_tile);
            }
            printf("Clic izquierdo detectado en (%d, %d)\n", mouseX, mouseY);
            player->activate_weapon();
            // bomba->activate();
        }
    }


    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;
            if (shop.get_activa()) {
                WeaponCode code = shop.calculate_selection(mouseX, mouseY);
                if (code != WeaponCode::NONE)  // Realmente esto no deberia de siquiera pasar, casi
                                               // que es una exception
                    controller.sender_buy_weapon(code);
            } else if (snapshot.game_state.state != GameState::TIME_TO_BUY)  // Quiza innecesaria
                controller.sender_shoot(mouseX, mouseY);
            // player->activate_weapon(Weapon::AK47);
            //  bomba->activate();
            printf("Clic izquierdo detectado en (%d, %d)\n", mouseX, mouseY);
        }
    }

    return true;
}


bool GameView::add_player(float x, float y, int speed, const Claves_skins& claves) {
    this->player = new PlayerView(x, y, claves, speed, &camera, &manger_texture, config);
    return true;
}


void GameView::initial_draw_game(const GameInfo& info_game_view /*,const Player& info_game*/) {

    this->map = new MapView(info_game_view.map_info, &camera, &manger_texture, config);
    if (!map) {
        throw std::runtime_error("Error al cargar mapa");
        return;
    }
    this->fov = new FieldOfView(*player, camera, manger_texture, config);
    shop.set_weapons_purchasables(info_game_view.weapons_purchasables);
}

void GameView::updates_game() {
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

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
void GameView::draw_object() {

    map->draw(*renderer);
    player->draw(*renderer);
    draw_players();
    // if (bomba)
    //    bomba->draw(*renderer);
    if (bullets.empty()) {
        std::cout << "sin balas\n";
    }
    for (size_t i = 0; i < bullets.size(); ++i) {
        Bullet& bullet = bullets[i];
        bullet.updateBullet(0.1f);
        if (bullet.finalizado()) {
            bullets.erase(bullets.begin() + i);
        } else {
            bullet.draw(*renderer);
        }
    }
    fov->draw(*renderer);
    if (shop.get_activa()) {
        shop.draw(*renderer);
    }
    // map->render_objet(*renderer);
    hud.render(*renderer);
}


void GameView::draw_game() {
    /*
    std::vector<std::pair<Coordenada, Coordenada>> balas_hardcodeadas = {
        {{2.0f, 3.0f}, {4.0f, 6.0f}},
        {{5.5f, 1.2f}, {8.0f, 2.0f}},
        {{0.0f, 0.0f}, {10.0f, 10.0f}}};

    for (const auto& par: balas_hardcodeadas) {
        const Coordenada& init = par.first;
        const Coordenada& end = par.second;

        Bullet bala(init, end, manger_texture.get(Object::BULLET));
        bullets.push_back(bala);

        std::cout << "Init: (" << init.x << ", " << init.y << "), ";
        std::cout << "End: (" << end.x << ", " << end.y << ")\n";
    }
    */

    SDL_Event event;
    bomba = new Bomb(0, 0, camera, manger_texture, config);
    auto keep_running = [&]() -> bool {
        while (SDL_PollEvent(&event)) {

            if (!handle_events(event)) {
                return false;
            }
        }
        return true;
    };
    auto game_step = [&]() {
        updates_game();
        SDL_RenderClear(renderer);
        draw_object();
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


    if (fov)
        delete fov;

    this->manger_texture.clear();

    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (ventana)
        SDL_DestroyWindow(ventana);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
