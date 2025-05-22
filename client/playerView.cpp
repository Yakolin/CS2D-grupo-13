#include "playerView.h"

const int FILAS_MAP = 17;
const int COLUMNAS_MAP = 38;

PlayerView::PlayerView(const float& x, const float& y, const std::string rute, const float& speed,
                       SDL_Rect* camera_reseiver, ManageTexture* manejador):
        fil(pasar_pixeles(x)),
        col(pasar_pixeles(y)),
        rutaPlayer(rute),
        origin_rect({0, 0, 64, 96}),
        destination_rect(
                {static_cast<int>(col) , static_cast<int>(fil) , 32, 32}),
        speed_player(speed),
        width_img(),
        height_img(),
        item({0, 0}),
        anglePlayer(),
        camera(camera_reseiver),
        manejador(manejador) {
    calcular();
}

int PlayerView::pasar_pixeles(const float& pos) { return pos * 32; }

void PlayerView::calcular() {

    SDL_Texture* tiles_player = manejador->get(Objet::PLAYER);
    if (!tiles_player) {
        std::cerr << "Error: No se pudo cargar la textura del jugador." << std::endl;
        return;
    }
    SDL_QueryTexture(tiles_player, nullptr, nullptr, &width_img, &height_img);
    // std::cout << "Ancho: " << width_img << ", Alto: " << height_img << std::endl;
}

void PlayerView::draw(SDL_Renderer& renderer) {

    SDL_Texture* tiles_player = manejador->get(Objet::PLAYER);
    origin_rect = {item.col * width_img, item.fil * height_img, width_img / 2, height_img / 3};
    //                           col=x               fil =y       ancho, alto
    destination_rect = {static_cast<int>(col) - camera->x, static_cast<int>(fil) - camera->y, 32,
                        32};
   
    // SDL_RenderCopy(&renderer, tiles_player, &origin_rect ,&destination_rect);
    SDL_RenderCopyEx(&renderer, tiles_player, &origin_rect, &destination_rect, anglePlayer, nullptr,
                     SDL_FLIP_NONE);
}

void PlayerView::add_speed(const SDL_Keycode& tecla) {
    if (tecla == SDLK_w || tecla == SDLK_UP) {  // arriba
        fil -= speed_player;
    } else if (tecla == SDLK_a || tecla == SDLK_LEFT) {  // izquierda
        col -= speed_player;
    } else if (tecla == SDLK_d || tecla == SDLK_RIGHT) {  // derecha
        col += speed_player;
    } else if (tecla == SDLK_s || tecla == SDLK_DOWN) {  // abajo
        fil += speed_player;
    }
    int fila_matriz = fil / 32;
    int columna_matriz = col / 32;
    std::cout << "Fila: " << fila_matriz << " Columna: " << columna_matriz << std::endl;

}

void PlayerView::update_view_angle(const int& mouse_x, const int& mouse_y) {

    int jugador_centro_x = destination_rect.x + destination_rect.w / 2;
    int jugador_centro_y = destination_rect.y + destination_rect.h / 2;

    int dx = mouse_x - jugador_centro_x;
    int dy = mouse_y - jugador_centro_y;

    // Ángulo en radianes
    float angulo = std::atan2(dy, dx);

    // Convertir a grados
    anglePlayer = angulo * 180.0f / M_PI;
}


float PlayerView::getFil() const { return fil; }

float PlayerView::getCol() const { return col; }
//
std::string PlayerView::getRutaPlayer() const { return rutaPlayer; }

float PlayerView::getSpeed() const { return speed_player; }

void PlayerView::setFil(float x) { fil = x; }

void PlayerView::setCol(float y) { col = y; }

void PlayerView::setRutaPlayer(const std::string& ruta) { rutaPlayer = ruta; }

void PlayerView::setSpeed(float speed) { speed_player = speed; }

int PlayerView::getWidthImg() const { return width_img; }

int PlayerView::getHeightImg() const { return height_img; }

float PlayerView::getAnglePlayer() const { return anglePlayer; }

PlayerView::~PlayerView() {}

