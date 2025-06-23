#include "gameView.h"

#include <unordered_set>

#include <SDL_mixer.h>


int counter2 = 0;

GameView::GameView(Socket& skt, const GameInfo& game_info, const Player& info_Player,
                   SDL_Window* ventana, SDL_Renderer* renderer, ManageTexture& manger_texture,
                   GameConfig& config):
        config(config),
        config_sound(config.get_volumen(), config.get_volumen_music()),
        controller(skt),
        constant_rate_loop([this]() { return this->should_keep_running(); },
                           [this]() { this->step(); }),
        ventana(ventana),
        renderer(renderer),
        camera(config.get_window_width(), config.get_window_height()),
        manger_texture(manger_texture),
        player(new PlayerView(11, 4, load_claves(info_Player), 50.0f, &camera, &manger_texture,
                              config)),
        players(),
        snapshot(),
        map(new MapView(game_info.map_info, &camera, &manger_texture, config)),
        fov(new FieldOfView(*player, camera, manger_texture, config)),
        shop(camera, manger_texture, config),
        bomba(new Bomb(500, 500, camera, manger_texture, config)),
        hud(config, manger_texture, info_Player.info),
        bullets(),
        activa(false),
        bomb_activate(false),
        keep_running(true),
        events(controller, config, camera, *player, players, snapshot, *map, *fov, *bomba, shop,
               hud, keep_running, config_sound, manger_texture) {

    shop.set_weapons_purchasables(game_info.weapons_purchasables);
    config_sound.play_music(Music::SALA_ESPERA, -1);
}

Skins GameView::load_claves(const Player& info_Player) {
    return Skins(controller.toItemCounterTerrorism(info_Player.skin_ct),
                 controller.toItemTerrorism(info_Player.skin_tt));
}

void GameView::reset_values(PlayerView* player, const float& x_pixeles, const float& y_pixeles) {

    player->setPrevPos(player->getXActual(), player->getYActual());
    player->setTargetPos(x_pixeles, y_pixeles);
    player->setInterpTime(0.0f);
    player->setInterpDuration(0.1f);
}

void GameView::update_bullets_snapshot() {
    int tile_width = config.get_tile_width();
    int tile_height = config.get_tile_height();
    for (const BulletImage& bullet: snapshot.bullets_in_air) {
        Coordenada init = {static_cast<float>(bullet.initial.x * tile_width),
                           static_cast<float>(bullet.initial.y * tile_height)};
        Coordenada end = {static_cast<float>(bullet.end.x * tile_width),
                          static_cast<float>(bullet.end.y * tile_height)};

        Bullet bullet_aux(init, end, bullet.width, bullet.code);
        this->bullets.push_back(bullet_aux);
    }
}


void GameView::handle_bomb_sound() {

    BombState state = snapshot.bomb.state;
    if (last_state_bomb != BombState::DESACTIVATED && state == BombState::DESACTIVATED) {
        config_sound.play_sound(EffectType::DESACTIVATED, 0);
    } else if (last_state_bomb != BombState::EXPLOTED && state == BombState::EXPLOTED) {
        config_sound.play_sound(EffectType::EXPLOSION, 0);
    }
}

void GameView::handle_state_game() {
    GameState state = snapshot.game_state.state;
    if (state == GameState::ROUND_STARTED)
        config_sound.set_round(false);
    if (snapshot.bomb.state != BombState::ACTIVATED) {
        config_sound.set_bomb(false);
        bomba_timer.stop();
    }
    if (config_sound.get_round_sound())
        return;

    if (state == GameState::CT_WIN_GAME || state == GameState::CT_WIN_ROUND) {
        config_sound.play_sound(EffectType::WIN_CT, 0);
        config_sound.set_round(true);
    } else if (state == GameState::TT_WIN_GAME || state == GameState::TT_WIN_ROUND) {
        config_sound.play_sound(EffectType::WIN_TT, 0);
        config_sound.set_round(true);
    }
}


void GameView::update_sounds(const PlayerImage& player) {

    Uint16 angle = this->player->getAnglePlayer();
    for (const auto& sound: player.heared_sounds.common_sounds) {
        Uint8 distance = static_cast<Uint8>(sound.distance);
        config_sound.play_effect_with_position(sound.type, angle, distance);
    }

    for (const auto& shoot_sound: player.heared_sounds.shoot_sounds) {
        Uint8 distance = static_cast<Uint8>(shoot_sound.distance);
        config_sound.play_shoot_with_position(shoot_sound.code, angle, distance);
    }
    handle_state_game();
}

void GameView::delete_players_death() {

    std::unordered_set<player_id_t> jugadores_vivos;
    for (const auto& player_img: snapshot.players_images) {
        jugadores_vivos.insert(player_img.player_id);
    }

    auto it = players.begin();
    while (it != players.end()) {
        if (jugadores_vivos.find(it->first) == jugadores_vivos.end()) {
            delete it->second;
            it = players.erase(it);
        } else {
            ++it;
        }
    }
}

void GameView::update_status_game() {

    if (snapshot.game_state.state == GameState::CT_WIN_GAME ||
        snapshot.game_state.state == GameState::TT_WIN_GAME) {
        this->keep_running = false;
        controller.stop();
        throw GameFinishExeption("La partida ha finalizado.");
    }

    int tile_width = config.get_tile_width();
    int tile_height = config.get_tile_height();
    update_bullets_snapshot();
    bomba->update_bomb(snapshot.bomb);
    this->map->update_weapon_dropped(snapshot.dropped_things);
    if (!config_sound.get_bomb_sound() && snapshot.bomb.state == BombState::ACTIVATED) {
        config_sound.set_bomb(true);
        bomba_timer.start(snapshot.game_state.time);
    }
    handle_bomb_sound();
    last_state_bomb = snapshot.bomb.state;
    for (PlayerImage& player_img: this->snapshot.players_images) {
        player_id_t id = player_img.player_id;

        float x_pixeles = player_img.position.x * tile_width;
        float y_pixeles = player_img.position.y * tile_height;

        if (id == snapshot.client_id) {
            reset_values(player, x_pixeles, y_pixeles);
            player->update_weapons(player_img.weapons);
            player->update_equip(player_img);
            if (player_img.health <= 0) {
                player->set_muerto(true);
            } else {
                player->set_muerto(false);
            }
            update_sounds(player_img);

        } else if (players.find(id) == players.end()) {

            PlayerView* nuevo_jugador = new PlayerView(x_pixeles, y_pixeles, player_img.skin, 50.0f,
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
            player_aux->update_equip(player_img);
            reset_values(player_aux, x_pixeles, y_pixeles);
            player_aux->update_weapons(player_img.weapons);
            if (player_img.health <= 0) {
                player_aux->set_muerto(true);
            } else {
                player_aux->set_muerto(false);
            }
        }
    }

    delete_players_death();
}

void GameView::draw_players() {
    for (auto& pair: this->players) {
        PlayerView* player = pair.second;
        if (player && fov->is_in_fov(*player)) {
            player->draw(*renderer);
        }
    }
}
void GameView::draw_timer_bomb() {

    if (bomba_timer.debe_dibujar_flash()) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 80);
        SDL_Rect pantalla = {0, 0, config.get_window_width(), config.get_window_height()};
        SDL_RenderFillRect(renderer, &pantalla);
    }
}

void GameView::process_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        this->events.handle_events(event);
    }
    events.update_mouse_hold();
}

void GameView::update_game() {
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - this->lastTime) / 1000.0f;
    this->lastTime = currentTime;

    update_status_game();
    player->update(deltaTime);
    bomba_timer.update(config_sound, snapshot.game_state.time);

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
    // map->render_objet(*renderer);
    fov->draw(*renderer);
    if (shop.get_activa()) {
        shop.draw(*renderer);
    }
    hud.render(*renderer);
    draw_timer_bomb();
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

std::map<player_id_t, InfoPlayer> GameView::get_info_players_map() {

    std::map<player_id_t, InfoPlayer> info_map;
    for (const auto& player: snapshot.players_images) {
        InfoPlayer info;
        info.team = (player.team == Team::CT) ? "CT" : "TT";
        info.puntos = player.points;
        info.deaths = player.deaths;
        info.kills = player.kills;
        info.collected_money = player.collected_money;
        info_map[player.player_id] = info;
    }

    return info_map;
}

void GameView::run() {
    this->controller.start();
    this->constant_rate_loop.execute();
}

void GameView::step() {
    this->process_events();
    if (this->update_game_image()) {
        if (!config_sound.get_state_game()) {
            config_sound.stop_music();
            config_sound.play_music(Music::JUEGO, -1);
        }
        config_sound.set_start_game(true);
        this->update_game();
        this->render_game();
    }
}

GameView::~GameView() {
    for (auto& p: players) delete p.second;
    players.clear();
    delete player;
    player = nullptr;
    if (map)
        delete map;
    if (fov)
        delete fov;
}
