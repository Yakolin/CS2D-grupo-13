#include "playerView.h"

#include "mapView.h"

const int FILAS_MAP = 17;
const int COLUMNAS_MAP = 38;

PlayerView::PlayerView(const float& x, const float& y, const std::string& rute, const float& speed,
                       Camera* camera_receiver, ManageTexture* manager_texture, GameConfig& config):
        config(config),
        fil(y),
        col(x),
        rutaPlayer(rute),
        origin_rect({0, 0, 64, 96}),
        destination_rect({static_cast<int>(col), static_cast<int>(fil), 32, 32}),
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
        texture_player(nullptr) {
    calcular();

    texture_player = manejador->get(Object::GIGN);
    WeaponView* ak47 = new WeaponView(*camera, *manejador, WeaponCode::AK47, x, y, anglePlayer);
    weapons[WeaponCode::AK47] = ak47;
}

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


void PlayerView::update(const float& deltaTime) {

    if (interp_time < interp_duration) {
        interp_time += deltaTime;
        float t = std::min(interp_time / interp_duration, 1.0f);
        x_actual = prev_pos.x + (target_pos.x - prev_pos.x) * t;
        y_actual = prev_pos.y + (target_pos.y - prev_pos.y) * t;
    } else {
        x_actual = target_pos.x;
        y_actual = target_pos.y;
    }
}

void PlayerView::calcular() {

    SDL_Texture* tiles_player = manejador->get(Object::GUERRILLA);
    if (!tiles_player) {
        std::cerr << "Error: No se pudo cargar la textura del jugador." << std::endl;
        return;
    }
    SDL_QueryTexture(tiles_player, nullptr, nullptr, &width_img, &height_img);
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

void PlayerView::activate_weapon(const WeaponCode& weapon) {
    if (weapons.find(weapon) != weapons.end()) {
        activar_weapon = true;
        weapons[weapon]->setUsed(true);
    } else {
        std::cerr << "Error: Arma no encontrada." << std::endl;
    }
}
void PlayerView::draw(SDL_Renderer& renderer) {

    origin_rect = {item.col * width_img, item.fil * height_img, width_img / 2, height_img / 3};

    destination_rect = {static_cast<int>(x_actual) - camera->getX(),  // col=x
                        static_cast<int>(y_actual) - camera->getY(),  // fil =y
                        config.get_tile_width(),                      // ancho
                        config.get_tile_height()};                    // alto
    SDL_RenderCopyEx(&renderer, texture_player ,&origin_rect, &destination_rect, anglePlayer, nullptr,
                     SDL_FLIP_NONE);

    if (activar_weapon) {

        WeaponView* weapon_view = weapons[WeaponCode::AK47];
        weapon_view->update(static_cast<int>(x_actual), static_cast<int>(y_actual), anglePlayer);
        weapon_view->draw(renderer);
    }
}


void PlayerView::update_view_angle(const int& mouse_x, const int& mouse_y) {

    int jugador_centro_x = destination_rect.x + destination_rect.w / 2;
    int jugador_centro_y = destination_rect.y + destination_rect.h / 2;

    int dx = mouse_x - jugador_centro_x;
    int dy = mouse_y - jugador_centro_y;

    // Ángulo en radianes
    float angulo = std::atan2(dx, -dy);

    // Convertir a grados
    anglePlayer = angulo * 180.0f / M_PI;
}


float PlayerView::getFil() const { return fil; }

float PlayerView::getCol() const { return col; }
//
std::string PlayerView::getRutaPlayer() const { return rutaPlayer; }

float PlayerView::getSpeed() const { return speed_player; }

void PlayerView::setFil(float y_world) { fil = y_world; }

void PlayerView::setCol(float x_world) { col = x_world; }


void PlayerView::setXActual(float x) { x_actual = x; }
void PlayerView::setYActual(float y) { y_actual = y; }


float PlayerView::getXActual() { return x_actual; }
float PlayerView::getYActual() { return y_actual; }

void PlayerView::setRutaPlayer(const std::string& ruta) { rutaPlayer = ruta; }

void PlayerView::setSpeed(float speed) { speed_player = speed; }

int PlayerView::getWidthImg() const { return width_img; }

int PlayerView::getHeightImg() const { return height_img; }

float PlayerView::getAnglePlayer() const { return anglePlayer; }

void PlayerView::setVelX(float vx) { velocity_x = vx; }
void PlayerView::setVelY(float vy) { velocity_y = vy; }
float PlayerView::getVelX() const { return velocity_x; }
float PlayerView::getVelY() const { return velocity_y; }


PlayerView::~PlayerView() {}
