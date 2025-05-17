#include "playerView.h"

const int FILAS_MAP =17;
const int COLUMNAS_MAP =38;

PlayerView::PlayerView(const float& x , const float& y, const std::string rute, const float& speed ):
    fil(pasar_pixeles(x)),
    col(pasar_pixeles(y)),
    rutaPlayer(rute),
    origin_rect(nullptr),
    destination_rect({static_cast<int>(col)* COLUMNAS_MAP, static_cast<int>(fil)* FILAS_MAP, 32, 32}),
    speed_player(speed) 
   // texture_player(nullptr)
    {}


int PlayerView::pasar_pixeles(const float& pos){
    return pos * 32;
}

void PlayerView::draw_player(SDL_Renderer* renderer, SDL_Texture* tiles_player){

   // SDL_QueryTexture(texture_players, nullptr, nullptr, &ancho, &alto);
   // std::cout << "Ancho: " << ancho << ", Alto: " << alto << std::endl;

     //                           col=x               fil =y       ancho, alto
    destination_rect = {static_cast<int>(col), static_cast<int>(fil),32, 32};
    //obtener_medidas(tiles);
    SDL_RenderCopy(renderer, tiles_player, origin_rect ,&destination_rect);

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
PlayerView::~PlayerView(){

}

/*

void PlayerView::setTexturePlayer(SDL_Texture* texture) {
    texture_player = texture;
}
    */
//{0, 0,209, 208}
/*void obtener_medidas(SDL_Texture* tiles){
    int ancho, alto;
    SDL_QueryTexture(tiles, nullptr, nullptr, &ancho, &alto);
    std::cout << "Ancho: " << ancho << ", Alto: " << alto << std::endl;
}*/
/* mov por casillas crea un cuadradito con posicion
                            col=x               fil =y       ancho, alto
    SDL_Rect jugadorRect = { jugadorColumna * 38, jugadorFila * 17, 32, 32 };
    dibuja  //! nullptr detern¿mina que sprite sheet queres usar
    SDL_RenderCopy(renderer, tiles_players, nullptr, &jugadorRect);

    */