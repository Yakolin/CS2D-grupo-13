#include "playerView.h"

#include "mapView.h"

const int FILAS_MAP = 17;
const int COLUMNAS_MAP = 38;

PlayerView::PlayerView(const float& x, const float& y, const Claves_skins& clave_player,
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
        player_id(),  //! cambiar
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
        texture_player(manejador->get_texture_ct(clave_player.ct_skin)),
        equipped_weapon(WeaponCode::NONE),
        lastUpdateTime(0) {
    calcular();
    lastUpdateTime = SDL_GetTicks();
}

void PlayerView::update_equip(const PlayerImage player_aux){
    this->equipped_weapon = player_aux.equipped_weapon;
}

void imprimir_weapons_vec(const std::vector<WeaponImage>& weapons_vec) {
    if (weapons_vec.empty()) {
        std::cout << "El vector de armas está vacío." << std::endl;
        return;
    }

   // std::cout << "Armas del jugador:" << std::endl;


    for (const WeaponImage& weapon: weapons_vec) {
        if (weapon.weapon_code == WeaponCode::NONE) {
            std::cout << "  (Arma vacía / NONE, se salta)" << std::endl;
            continue;
        }
        std::cout << "  WeaponCode: " << static_cast<int>(weapon.weapon_code)
                  << ", Balas actuales: " << static_cast<int>(weapon.current_bullets)
                  << ", Cargador: " << static_cast<int>(weapon.magazine)
                  << ", Balas en inventario: " << static_cast<int>(weapon.inventory_bullets)
                  << std::endl;
    }
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
    //imprimir_weapons_vec(weapons_vec);

    for (const WeaponImage& weapon_img: weapons_vec) {
        WeaponCode weapon_key = weapon_img.weapon_code;

        if (weapon_key == WeaponCode::NONE)
            continue;

        if (!is_valid_weapon_code(weapon_key)) {
            std::cerr << "WeaponCode inválido recibido: " << static_cast<int>(weapon_key) << std::endl;
            continue;
        }
        if (this->weapons.find(weapon_key) != this->weapons.end()) {
            weapons[weapon_key]->update(x_actual, y_actual, anglePlayer);
        } else {
            weapons[weapon_key] = std::make_unique<WeaponView>(*camera, *manejador, weapon_key,
                                                               x_actual, y_actual, anglePlayer);
        }
    }
    //std::cout << "armas. cargadas ---------" << std::endl;
    /* for (const auto& par : weapons ) {
        std::cout << static_cast<int>(par.first) << std::endl;
    }*/
    
}


void PlayerView::calcular() {

    SDL_QueryTexture(texture_player, nullptr, nullptr, &width_img, &height_img);
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

void PlayerView::activate_weapon() {
    activar_weapon = true;
}
void PlayerView::draw(SDL_Renderer& renderer) {

    origin_rect = {item.col * width_img, item.fil * height_img, width_img / 2, height_img / 3};

    destination_rect = {static_cast<int>(x_actual) - camera->getX(),  // col=x
                        static_cast<int>(y_actual) - camera->getY(),  // fil =y
                        config.get_tile_width(),                      // ancho
                        config.get_tile_height()};                   // alto

    SDL_RenderCopyEx(&renderer, texture_player, &origin_rect, &destination_rect, anglePlayer,
                     nullptr, SDL_FLIP_NONE);

    if (this->equipped_weapon != WeaponCode::NONE) {
        //SDL_Point center;
        //center.x = x_actual;
        //center.y = y_actual ;
        WeaponView& weapon_view = *weapons[equipped_weapon];
        weapon_view.update(static_cast<int>(x_actual), static_cast<int>(y_actual), anglePlayer);
        weapon_view.draw(renderer);
    }
}

void PlayerView::update_view_angle(const int& mouse_x, const int& mouse_y) {
    int jugador_centro_x = destination_rect.x;
    int jugador_centro_y = destination_rect.y;

    // Ángulo en radianes (hacia el mouse)
    float angulo = std::atan2(mouse_x - jugador_centro_x,
                              -(mouse_y - jugador_centro_y));  // Esto esta bien

    // Convertir a grados
    anglePlayer = angulo * 180.0f / M_PI;
}

float PlayerView::getSpeed() const { return speed_player; }

void PlayerView::setXActual(float x) { x_actual = x; }
void PlayerView::setYActual(float y) { y_actual = y; }


float PlayerView::getXActual() { return x_actual; }
float PlayerView::getYActual() { return y_actual; }


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
