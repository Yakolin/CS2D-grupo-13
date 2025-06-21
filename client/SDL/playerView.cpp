#include "playerView.h"

#include "../tipos.h"

#include "mapView.h"

PlayerView::PlayerView(const float& x, const float& y, const Skins& clave_player,
                       const float& speed, Camera* camera_receiver, ManageTexture* manager_texture,
                       GameConfig& config):
        config(config),
        origin_rect({0, 0, 64, 96}),
        destination_rect({static_cast<int>(x), static_cast<int>(y), 32, 32}),
        speed_player(speed),
        width_img(),
        height_img(),
        item({0, 0}),
        anglePlayer(),
        camera(camera_receiver),
        manejador(manager_texture),
        clave_team(Team::CT),
        x_actual(x),
        y_actual(y),
        velocity_x(0),
        velocity_y(0),
        prev_pos({x, y}),
        target_pos({x, y}),
        interp_duration(0.1f),  // Duración de la interpolación en segundos
        interp_time(1.0f),
        weapons(),
        activar_weapon(false),
        muerto(false),
        equipped_weapon(WeaponCode::NONE),
        textures_player(load_claves(clave_player)) {
    SDL_Texture* texture_player = textures_player.at(clave_team);
    config.get_dimension(texture_player, width_img, height_img);
}
std::unordered_map<Team, SDL_Texture*> PlayerView::load_claves(const Skins& clave_player) {
    std::unordered_map<Team, SDL_Texture*> text;
    text[Team::CT] = manejador->get_texture_ct(clave_player.ct_skin);
    text[Team::TT] = manejador->get_texture_tt(clave_player.tt_skin);
    return text;
}

Team PlayerView::get_clave_team() { return clave_team; }

void PlayerView::set_muerto(const bool& new_state) { muerto = new_state; }

void PlayerView::update_equip(const PlayerImage player_aux) {
    this->equipped_weapon = player_aux.equipped_weapon;
    this->clave_team = player_aux.team;
}


void PlayerView::update(const float& deltaTime) {

    if (interp_time < interp_duration) {
        interp_time += deltaTime;
        float t = std::min(interp_time / interp_duration, 1.0f);
        x_actual = prev_pos.x + (target_pos.x - prev_pos.x) * t;
        y_actual = prev_pos.y + (target_pos.y - prev_pos.y) * t;
    }
}
bool is_valid_weapon_code(WeaponCode code) {
    switch (code) {
        case WeaponCode::BOMB:
        case WeaponCode::AK47:
        case WeaponCode::AWP:
        case WeaponCode::M3:
        case WeaponCode::KNIFE:
        case WeaponCode::GLOCK:
            return true;
        default:
            return false;
    }
}
void PlayerView::update_weapons(const std::vector<WeaponImage>& weapons_vec) {
    if (weapons_vec.empty()) {
        std::cout << "El jugador no tiene armas." << std::endl;
        return;
    }
    // imprimir_weapons_vec(weapons_vec);

    for (const WeaponImage& weapon_img: weapons_vec) {
        WeaponCode weapon_key = weapon_img.weapon_code;

        if (weapon_key == WeaponCode::NONE)
            continue;

        if (!is_valid_weapon_code(weapon_key)) {
            std::cerr << "WeaponCode inválido recibido: " << static_cast<int>(weapon_key)
                      << std::endl;
            continue;
        }
        if (this->weapons.find(weapon_key) != this->weapons.end()) {
            weapons[weapon_key]->update(x_actual, y_actual, anglePlayer);
        } else {
            weapons[weapon_key] = std::make_unique<WeaponView>(*camera, *manejador, weapon_key,
                                                               x_actual, y_actual, anglePlayer);
        }
    }
    // std::cout << "armas. cargadas ---------" << std::endl;
    /* for (const auto& par : weapons ) {
        std::cout << static_cast<int>(par.first) << std::endl;
    }*/
}


void PlayerView::add_speed(const SDL_Keycode& tecla) {
    if (tecla == SDLK_w || tecla == SDLK_UP) {
        setVelY(-speed_player);
    } else if (tecla == SDLK_s || tecla == SDLK_DOWN) {
        setVelY(speed_player);
    } else if (tecla == SDLK_a || tecla == SDLK_LEFT) {
        setVelX(-speed_player);
    } else if (tecla == SDLK_d || tecla == SDLK_RIGHT) {
        setVelX(speed_player);
    }
}
void PlayerView::stop_speed(const SDL_Keycode& tecla) {
    if (tecla == SDLK_w || tecla == SDLK_UP) {
        setVelY(0);
    } else if (tecla == SDLK_s || tecla == SDLK_DOWN) {
        setVelY(0);
    } else if (tecla == SDLK_a || tecla == SDLK_LEFT) {
        setVelX(0);
    } else if (tecla == SDLK_d || tecla == SDLK_RIGHT) {
        setVelX(0);
    }
}
void PlayerView::auxiliar(const SDL_Keycode& tecla) {

    if (tecla == SDLK_w || tecla == SDLK_UP) {  // arriba
        y_actual -= speed_player;
    } else if (tecla == SDLK_a || tecla == SDLK_LEFT) {  // izquierda
        x_actual -= speed_player;
    } else if (tecla == SDLK_d || tecla == SDLK_RIGHT) {  // derecha
        x_actual += speed_player;
    } else if (tecla == SDLK_s || tecla == SDLK_DOWN) {  // abajo
        y_actual += speed_player;
    }
}


void PlayerView::activate_weapon() { activar_weapon = true; }
void PlayerView::draw(SDL_Renderer& renderer) {

    SDL_Texture* texture_player;
    if (!muerto) {
        origin_rect = {item.col * width_img, item.fil * height_img, width_img / 2, height_img / 3};
        texture_player = textures_player.at(clave_team);
    } else {
        texture_player = manejador->get(Object::MUERTE);
        int tex_width, tex_height;
        SDL_QueryTexture(texture_player, nullptr, nullptr, &tex_width, &tex_height);
        origin_rect = {0, 0, tex_width, tex_height};
    }
    destination_rect = {static_cast<int>(x_actual) - camera->getX(),
                        static_cast<int>(y_actual) - camera->getY(), config.get_tile_width(),
                        config.get_tile_height()};  // alto
    SDL_RenderCopyEx(&renderer, texture_player, &origin_rect, &destination_rect, anglePlayer,
                     nullptr, SDL_FLIP_NONE);

    if (this->equipped_weapon != WeaponCode::NONE) {
        WeaponView& weapon_view = *weapons[equipped_weapon];
        weapon_view.update(static_cast<int>(x_actual), static_cast<int>(y_actual), anglePlayer);
        weapon_view.draw(renderer);
    }
}

void PlayerView::update_view_angle(const int& mouse_x, const int& mouse_y) {
    int jugador_centro_x = destination_rect.x;
    int jugador_centro_y = destination_rect.y;

    float angulo = std::atan2(mouse_x - jugador_centro_x,
                              -(mouse_y - jugador_centro_y));  // Esto esta bien
    anglePlayer = angulo * 180.0f / M_PI;
}

float PlayerView::getSpeed() const { return speed_player; }

void PlayerView::setXActual(float x) { x_actual = x; }
void PlayerView::setYActual(float y) { y_actual = y; }


float PlayerView::getXActual() const { return x_actual; }
float PlayerView::getYActual() const { return y_actual; }


void PlayerView::setSpeed(float speed) { speed_player = speed; }

int PlayerView::getWidthImg() const { return width_img; }

int PlayerView::getHeightImg() const { return height_img; }

float PlayerView::getAnglePlayer() const { return anglePlayer; }

void PlayerView::setVelX(float vx) { velocity_x = vx; }
void PlayerView::setVelY(float vy) { velocity_y = vy; }
float PlayerView::getVelX() const { return velocity_x; }
float PlayerView::getVelY() const { return velocity_y; }

void PlayerView::setPrevPos(const float& new_x, const float& new_y) {
    prev_pos.x = new_x;
    prev_pos.y = new_y;
}
void PlayerView::setTargetPos(const float& new_x, const float& new_y) {
    target_pos.x = new_x;
    target_pos.y = new_y;
}

void PlayerView::setInterpDuration(const float& duration) { interp_duration = duration; }
void PlayerView::setInterpTime(const float& time) { interp_time = time; }
int PlayerView::pasar_pixeles_x(const float& tile_x) { return tile_x * config.get_tile_width(); }

int PlayerView::pasar_pixeles_y(const float& tile_y) { return tile_y * config.get_tile_height(); }

PlayerView::~PlayerView() {}
