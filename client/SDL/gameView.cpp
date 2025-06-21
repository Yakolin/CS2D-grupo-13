#include "gameView.h"
#include <SDL_mixer.h>

int counter2 = 0;
GameView::GameView(
        Socket&& skt , const GameInfo& game_info,const Player& info_Player,SDL_Window* ventana, SDL_Renderer* renderer, ManageTexture& manger_texture,  GameConfig& config):  
        config_sound(),
        config(config),
        controller(std::move(skt)),
        constant_rate_loop([this]() { return this->should_keep_running(); },
                           [this]() { this->step(); }),
        ventana(ventana),
        renderer(renderer),
        camera(config.get_window_width(), config.get_window_height()),
        manger_texture(manger_texture),
        player(new PlayerView(11, 4,load_claves(info_Player),200.0f ,&camera, &manger_texture, config)),// !cambiar a 200.0f
        players(),
        snapshot(),
        map(new MapView(game_info.map_info, &camera, &manger_texture, config)),
        fov(nullptr),
        shop(camera, manger_texture, config),
        bomba(new Bomb(500,500,camera,manger_texture,config)),
        hud(config, manger_texture,info_Player.info),
        bullets(),
        activa(false),
        bomb_activate(false),
        keep_running(true) 
{
    config_sound.playMusic(Music::SALA_ESPERA,-1);
}



TerroristSkin toItemTerrorism(const std::string& str) {
    if (str == "Phoenix")
        return TerroristSkin::PHOENIX;
    if (str == "L337 Krew")
        return TerroristSkin::L337_KREW;
    if (str == "Arctic Avenger")
        return TerroristSkin::ARCTIC_AVENGER;
    return TerroristSkin::GUERRILLA;
}
CounterTerroristSkin toItemCounterTerrorism(const std::string& str) {
    if (str == "Seal Force")
        return CounterTerroristSkin::SEAL;
    if (str == "German GSG-9")
        return CounterTerroristSkin::GSG9;
    if (str == "UK SAS")
        return CounterTerroristSkin::SAS;
    return CounterTerroristSkin::GIGN;
}
Skins GameView::load_claves(const Player& info_Player){
    return Skins(toItemCounterTerrorism(info_Player.skin2),toItemTerrorism(info_Player.skin));
}


void GameView::reset_values(PlayerView* player, const float& x_pixeles, const float& y_pixeles) {

    player->setPrevPos(player->getXActual(), player->getYActual());
    player->setTargetPos(x_pixeles, y_pixeles);
    player->setInterpTime(0.0f);
    player->setInterpDuration(0.1f);
}

void print_game_image(const GameImage& image) {
    
    std::cout << "=== Game Image ===\n";
   std::cout << "Client ID: " << image.client_id << "\n";
    std::cout << "--- Players ---\n";
    for (const auto& player: image.players_images) {
        std::cout << "Player ID: " << player.player_id << "\n";
        std::cout << "  Position: (" << player.position.x << ", " << player.position.y << ")\n";
/*         std::cout << "  Health: " << static_cast<int>(player.health) << "\n";
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
         }*/
    }

/*    
    for (const auto& bullet: image.bullets_in_air) {
        std::cout << "  From (" << bullet.initial.x << ", " << bullet.initial.y << ") to ("
                  << bullet.end.x << ", " << bullet.end.y << ")\n";
    }
  */  
    std::cout << "--- Bomb ---\n";
    std::cout << "  Position: (" << image.bomb.position.x << ", " << image.bomb.position.y << ")\n";
    std::cout << "  State: " << static_cast<int>(image.bomb.state) << "\n";
 /* 
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



void GameView::update_bullets_snapshot(){
    int tile_width = config.get_tile_width();
    int tile_height = config.get_tile_height();
    for (const BulletImage& bullet: snapshot.bullets_in_air) {
        Coordenada init = {static_cast<float>(bullet.initial.x * tile_width),
                           static_cast<float>(bullet.initial.y * tile_height)};
        Coordenada end = {static_cast<float>(bullet.end.x * tile_width),
                          static_cast<float>(bullet.end.y * tile_height)};

        Bullet bullet_aux(init, end, manger_texture.get(Object::BULLET));
        this->bullets.push_back(bullet_aux);
    }
}


void GameView::update_status_game() {
    //print_game_image(snapshot);
    int tile_width = config.get_tile_width();
    int tile_height = config.get_tile_height();
    update_bullets_snapshot();
    bomba->update_bomb(snapshot.bomb);
    this->map->update_weapon_dropped(snapshot.dropped_things);

    for (PlayerImage& player_img: this->snapshot.players_images) {
        player_id_t id = player_img.player_id;

        float x_pixeles = player_img.position.x * tile_width;
        float y_pixeles = player_img.position.y * tile_height;

        if (id == snapshot.client_id) {
            reset_values(player, x_pixeles, y_pixeles);
            player->update_weapons(player_img.weapons);
            player->update_equip(player_img);
            if(player_img.health <=0){
                player->set_muerto(true);
            }else{
                player->set_muerto(false);
            }

        } else if (players.find(id) == players.end()) {

            PlayerView* nuevo_jugador = new PlayerView(x_pixeles, y_pixeles, player_img.skin, 200.0f,
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
            if(player_img.health <= 0){
                player_aux->set_muerto(true);
            }else{
                player_aux->set_muerto(false);
            }
        }
    }
}

void GameView::draw_players() {
    for (auto& pair: this->players) {
        PlayerView* player = pair.second;
        if (player && fov->is_in_fov(*player)) {
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
   // player->auxiliar(tecla); //todo comentar
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
    if (snapshot.game_state.state == GameState::ROUND_STARTED) {
        int mousex_tile = -1;
        int mousey_tile = -1;
        mouse_position_tiles(mousex_tile, mousey_tile, mouseX, mouseY);
        controller.sender_shoot(mousex_tile, mousey_tile);
    }
}


/*void GameView::handle_sprite_mouse(const int& mousex, const int& mousey){
    int tile_mousex=0;
    int tile_mousey=0;
    mouse_position_tiles(tile_mousex,tile_mousey,mousex,mousey);
    for (auto& [id, player] : this->players){
        int tile_playerx= player->getXActual()/ config.get_tile_width();
        int tile_playery= player->getYActual() / config.get_tile_height();
        if(tile_mousex == tile_playerx && tile_mousey == tile_playery){
            
        }
    }
}*/

void GameView::update_window(){
    if(!config_sound.get_state_game()){
        SDL_Texture* textura = manger_texture.get(Object::FONDO_ESPERA);
        SDL_RenderCopy(renderer, textura, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }
}
void GameView::handle_events(const SDL_Event& event) {
    try {
        if (event.type == SDL_QUIT) {
            this->controller.stop();
            this->keep_running = false;
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
                update_window();
                this->map->update_map_dimensions();
                printf("Nuevo mapa width: %d, height: %d\n", map->getMapWidth(),
                       map->getMapHeight());
            }
        }

        if (event.type == SDL_MOUSEMOTION) {  // para mover mouse
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;
            hud.update_mouse(mouseX,mouseY);
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

void GameView::start(const GameInfo& info_game_view ) {

    this->fov = new FieldOfView(*player, camera, manger_texture, config);
    shop.set_weapons_purchasables(info_game_view.weapons_purchasables);
}

void GameView::process_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        this->handle_events(event);
    }
}

void GameView::update_game() {
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - this->lastTime) / 1000.0f;
    this->lastTime = currentTime;

    update_status_game();
    player->update(deltaTime);//! desconetar

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
    map->draw_weapon_dropped(*renderer);
    map->draw_zones(*renderer);
    player->draw(*renderer);
    draw_players();
    bomba->draw(*renderer);
    for (auto it = bullets.begin(); it != bullets.end();) {
        if (it->finalizado()) {
            it = bullets.erase(it);
        } else {
            Coordenada camera_pos(camera.getX(), camera.getY());
            it->set_camera(camera_pos);
            it->draw(*renderer);
            ++it;
        }
    }
    fov->draw(*renderer);
    if (shop.get_activa()) {
        shop.draw(*renderer);
    }
    // map->render_objet(*renderer);
    hud.render(*renderer);
    SDL_RenderPresent(renderer);
}

bool GameView::update_game_image() {
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
            return true;
        }
        return false;
    } catch (const ClosedQueue& e) {  // comportamiento esperado
        this->controller.stop();
    }
    return false;
}

bool GameView::should_keep_running() { return this->keep_running; }

void GameView::run() {
    this->controller.start();
    this->constant_rate_loop.execute();
}

void GameView::step() {
    this->process_events();
    if(this->update_game_image()){
        if(!config_sound.get_state_game()) {config_sound.stopMusic();}
        config_sound.set_start_game(true);
        this->update_game();
        this->render_game();
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
}
