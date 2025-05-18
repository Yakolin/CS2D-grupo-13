#include "playerView.h"

const int FILAS_MAP =17;
const int COLUMNAS_MAP =38;

PlayerView::PlayerView(const float& x , const float& y, const std::string rute, const float& speed ):
    fil(pasar_pixeles(x)),
    col(pasar_pixeles(y)),
    rutaPlayer(rute),
    origin_rect({0,0,64,96}),
    destination_rect({static_cast<int>(col)* COLUMNAS_MAP, static_cast<int>(fil)* FILAS_MAP, 32, 32}),
    speed_player(speed) ,
    width_img(),
    height_img(),
    item({0,0}),
    anglePlayer()
    {}

int PlayerView::pasar_pixeles(const float& pos){
    return pos * 32;
}

void PlayerView::draw_player(SDL_Renderer* renderer, SDL_Texture* tiles_player,const  MedidasSprites& sprite,const SDL_Rect& camera){

    origin_rect = {item.col * sprite.width,item.fil * sprite.height, sprite.width/2,sprite.height/3};
     //                           col=x               fil =y       ancho, alto
    destination_rect = {static_cast<int>(col) - camera.x ,
                        static_cast<int>(fil) - camera.y,
                        32, 32};
   // SDL_RenderCopy(renderer, tiles_player, &origin_rect ,&destination_rect);
    SDL_RenderCopyEx(renderer, tiles_player, &origin_rect, &destination_rect, anglePlayer,nullptr, SDL_FLIP_NONE);

}

void PlayerView::add_speed(const SDL_Keycode& tecla){
    
    if (tecla == SDLK_UP) { // arriba
        fil -= speed_player;
    } else if (tecla == SDLK_LEFT) { 
        col -= speed_player;
    } else if (tecla == SDLK_RIGHT) {
        col += speed_player;
    } else if (tecla == SDLK_DOWN) {
        fil += speed_player;
    }
}
void PlayerView::update_view_angle(const int& mouse_x,const int& mouse_y){

    int jugador_centro_x = destination_rect.x + destination_rect.w / 2;
    int jugador_centro_y = destination_rect.y + destination_rect.h / 2;

    int dx = mouse_x - jugador_centro_x;
    int dy = mouse_y - jugador_centro_y;

    // Ángulo en radianes
    float angulo = std::atan2(dy, dx);

    // Convertir a grados
    anglePlayer = angulo * 180.0f / M_PI;
}



float PlayerView::getFil() const {
    return fil;
}

float PlayerView::getCol() const {
    return col;
}
// 
std::string PlayerView::getRutaPlayer() const {
    return rutaPlayer;
}

float PlayerView::getSpeed() const {
    return speed_player;
}

void PlayerView::setFil(float x) {
    fil = x;
}

void PlayerView::setCol(float y) {
    col = y;
}

void PlayerView::setRutaPlayer(const std::string& ruta) {
    rutaPlayer = ruta;
}

void PlayerView::setSpeed(float speed) {
    speed_player = speed;
}

int PlayerView::getWidthImg() const {
    return width_img;
}

int PlayerView::getHeightImg() const {
    return height_img;
}

float PlayerView::getAnglePlayer() const {
    return anglePlayer;
}

PlayerView::~PlayerView(){

}

