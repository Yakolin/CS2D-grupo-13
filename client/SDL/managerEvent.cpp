#include "managerEvent.h"

#define HOLD_THRESHOLD_MS 200
#define BURST_INTERVALS_MS 100

ManagerEvent::ManagerEvent(Controller& controller, GameConfig& config, Camera& camera,
                           PlayerView& player, std::map<player_id_t, PlayerView*>& players,
                           GameImage& snapshot, MapView& map, FieldOfView& fov, Bomb& bomba,
                           Shopping& shop, HUD& hud, std::atomic<bool>& keep_running,
                           SoundConfig& sound, ManageTexture& manger_texture):
        controller(controller),
        config(config),
        camera(camera),
        player(player),
        players(players),
        snapshot(snapshot),
        map(map),
        fov(fov),
        shop(shop),
        bomba(bomba),
        hud(hud),
        keep_running(keep_running),
        left_mouse_pressed(false),
        mouse_press_start_time(0),
        last_burst_time(0),
        press_start_x(0),
        press_start_y(0),
        blocking_mouse_motion(false),
        config_sound(sound),
        manger_texture(manger_texture) {}

void ManagerEvent::handle_equip_type(const SDL_Keycode& tecla) {
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

void ManagerEvent::mouse_position_tiles(int& posx, int& posy, const int& mousex,
                                        const int& mousey) {
    const int TILE_SIZE = 32;

    int camX = camera.getX();
    int camY = camera.getY();
    int mapPixelX = mousex + camX;
    int mapPixelY = mousey + camY;

    posx = mapPixelX / TILE_SIZE;
    posy = mapPixelY / TILE_SIZE;
}

void ManagerEvent::handle_movements(SDL_Keycode& tecla) {
    if (tecla == SDLK_w || tecla == SDLK_UP)
        controller.sender_move(MoveType::DOWN);
    if (tecla == SDLK_s || tecla == SDLK_DOWN)
        controller.sender_move(MoveType::UP);
    if (tecla == SDLK_a || tecla == SDLK_LEFT)
        controller.sender_move(MoveType::LEFT);
    if (tecla == SDLK_d || tecla == SDLK_RIGHT)
        controller.sender_move(MoveType::RIGHT);
    player.add_speed(tecla);
}

void ManagerEvent::handle_extras(SDL_Keycode& tecla) {
    if (tecla == SDLK_g)
        controller.sender_drop();
    if (tecla == SDLK_r)
        controller.sender_reload();
    if (tecla == SDLK_e)
        controller.sender_defuse();
}

void manejarCursor(CursorContext contexto) {
    switch (contexto) {
        case CursorContext::NORMAL:
            std::cout << "Cursor normal.\n";
            break;
        case CursorContext::ENEMY:
            std::cout << "Cursor enemigo.\n";
            break;
        case CursorContext::ALLY:
            std::cout << "Cursor aliado.\n";
            break;
        default:
            break;
    }
}

void ManagerEvent::handle_key_down(SDL_Keycode& tecla) {
    if (snapshot.game_state.state != GameState::TIME_TO_BUY)
        shop.desactivate_shop();
    if (tecla == SDLK_b && snapshot.game_state.state == GameState::TIME_TO_BUY) {
        shop.activate_shop();
    }
    handle_movements(tecla);
    handle_equip_type(tecla);
    handle_extras(tecla);
}

void ManagerEvent::handle_single_left_click(int mouseX, int mouseY) {
    if (snapshot.game_state.state == GameState::ROUND_STARTED) {
        int mousex_tile = -1;
        int mousey_tile = -1;
        mouse_position_tiles(mousex_tile, mousey_tile, mouseX, mouseY);
        controller.sender_shoot(mousex_tile, mousey_tile);
    }
}

void ManagerEvent::send_burst() {
    if (snapshot.game_state.state == GameState::ROUND_STARTED) {
        int tx = -1, ty = -1;
        mouse_position_tiles(tx, ty, press_start_x, press_start_y);
        controller.sender_shoot_burst(tx, ty);
        this->blocking_mouse_motion = true;
    }
}

void ManagerEvent::update_mouse_hold() {
    if (!left_mouse_pressed)
        return;

    hold_mouse_t now = SDL_GetTicks();
    hold_mouse_t held = now - mouse_press_start_time;
    if (held < HOLD_THRESHOLD_MS)
        return;

    if (last_burst_time == 0) {
        last_burst_time = now;
        send_burst();
        return;
    }

    if (now - last_burst_time >= BURST_INTERVALS_MS) {
        last_burst_time = now;
        send_burst();
    }
}

void ManagerEvent::update_window() {
    if (!config_sound.get_state_game()) {
        SDL_Texture* textura = manger_texture.get(Object::FONDO_ESPERA);
        manger_texture.draw(textura);
    }
}


void ManagerEvent::handle_events(const SDL_Event& event) {
    try {
        if (event.type == SDL_QUIT || this->snapshot.game_state.state == GameState::GAME_ENDED) {
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
            player.stop_speed(tecla);  // Detiene movimiento
        }
        if (event.type == SDL_WINDOWEVENT) {  // LA PANTALLA
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                update_window();
                this->map.update_map_dimensions();
                map.getMapHeight();
            }
        }
        if (event.type == SDL_MOUSEMOTION && !this->blocking_mouse_motion) {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;
            hud.update_mouse(mouseX, mouseY);
            player.update_view_angle(mouseX, mouseY);
            controller.sender_pos_mouse(mouseX, mouseY);
        }
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            left_mouse_pressed = true;
            mouse_press_start_time = SDL_GetTicks();
            last_burst_time = 0;
            press_start_x = event.button.x;
            press_start_y = event.button.y;
            if (shop.get_activa()) {
                config_sound.play_sound(EffectType::MOUSE,0);
                auto code = shop.calculate_selection(press_start_x, press_start_y);
                if (code != WeaponCode::NONE)
                    controller.sender_buy_weapon(code);
            }
        }
        if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
            this->blocking_mouse_motion = false;
            bool was_pressed = left_mouse_pressed;
            left_mouse_pressed = false;
            hold_mouse_t held = SDL_GetTicks() - mouse_press_start_time;
            if (was_pressed && held < HOLD_THRESHOLD_MS) {
                handle_single_left_click(event.button.x, event.button.y);
            }
        }
    } catch (const ClosedQueue&
                     e) {  // Si la cola se cierra, significa que el servidor se ha cerrado
        this->controller.stop();
    }
}