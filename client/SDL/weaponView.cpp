
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
    std::cout << "Dibujando arma en piso en x: " << destination_rect.x 
              << ", y: " << destination_rect.y << std::endl;

    SDL_RenderCopyEx(&renderer, weaponTexture, nullptr, &destination_rect, angleWeapon, nullptr,
                     SDL_FLIP_NONE);
}
void WeaponView::update(const int& x_player, const int& y_player, const float& angle) {

    int offsetX = 20;
    int offsetY = 2;
    angleWeapon = angle;

    destination_rect.x = static_cast<int>(x_player + offsetX) - camera.getX();
    destination_rect.y = static_cast<int>(y_player + offsetY) - camera.getY();
    destination_rect.w = 15;
    destination_rect.h = 15;


}

void WeaponView::setUsed(bool used) { is_used = used; }
bool WeaponView::getUsed() { return is_used; }
