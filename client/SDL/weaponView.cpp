
#include "weaponView.h"


void WeaponView::draw(SDL_Renderer& renderer) {
    (void)renderer;
    // Implementación del método de dibujo del arma
    std::cout << "Dibujando el arma en la vista." << std::endl;
}
void WeaponView::update() {
    // Implementación del método de actualización del arma
    std::cout << "Actualizando el estado del arma." << std::endl;
}
void WeaponView::shoot() {
    // Implementación del método de disparo del arma
    std::cout << "Disparando el arma." << std::endl;
}
