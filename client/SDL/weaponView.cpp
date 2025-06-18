
#include "weaponView.h"

WeaponView::WeaponView(Camera& camera, ManageTexture& managertexture, const WeaponCode& clave,
                       const float& x, const float& y, const float& angle):
        manager(managertexture),
        weaponTexture(managertexture.get_weapon(clave)),
        destination_rect({static_cast<int>(x), static_cast<int>(y), 64, 64}),
        angleWeapon(angle),
        is_used(false),
        camera(camera)
        {
}


void WeaponView::draw(SDL_Renderer& renderer) {

    SDL_RenderCopyEx(&renderer, weaponTexture, nullptr, &destination_rect, angleWeapon, nullptr,
                     SDL_FLIP_NONE);
}

void WeaponView::draw_dropped(SDL_Renderer& renderer) {
    
    destination_rect.x -= camera.getX();
    destination_rect.y -= camera.getY();
    destination_rect.w = 32;
    destination_rect.h = 32;

    SDL_RenderCopyEx(&renderer, weaponTexture, nullptr, &destination_rect, angleWeapon, nullptr,
                     SDL_FLIP_NONE);
}
void WeaponView::update(const int& x_player, const int& y_player, const float& angle) {
/*
    int offsetX = 20;
    int offsetY = 2;
    angleWeapon = angle;

    destination_rect.x = static_cast<int>(x_player + offsetX) - camera.getX();
    destination_rect.y = static_cast<int>(y_player + offsetY) - camera.getY();
    destination_rect.w = 15;
    destination_rect.h = 15;
    */

    // Centro del jugador (usando 32 como tamaño del sprite del jugador)
int jugador_centro_x = x_player + 32 / 2;
int jugador_centro_y = y_player + 32 / 2;

destination_rect.w = 15;
destination_rect.h = 15;

// Distancia desde el centro del jugador hasta el arma
int distancia = 14;  // <--- Reducí la distancia

// Ángulo en radianes
float rad = angle * M_PI / 180.0f;

// Ajuste para ubicarla en la mano izquierda
int arma_x = jugador_centro_x - std::cos(rad) * distancia;  // <--- signo negativo
int arma_y = jugador_centro_y - std::sin(rad) * distancia;  // <--- signo negativo


arma_y += 4;
arma_x += 6;

destination_rect.x = arma_x - camera.getX() - destination_rect.w / 2;
destination_rect.y = arma_y - camera.getY() - destination_rect.h / 2;

angleWeapon = angle;

}


void WeaponView::setUsed(bool used) { is_used = used; }
bool WeaponView::getUsed() { return is_used; }
