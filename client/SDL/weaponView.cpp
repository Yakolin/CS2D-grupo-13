
#include "weaponView.h"

WeaponView::WeaponView(Camera& camera, ManageTexture& managertexture, const WeaponCode& clave,
                       const float& x, const float& y, const float& angle):
        manager(managertexture),
        weaponTexture(managertexture.get_weapon(clave)),
        // bullet_texture(managertexture.get(Object::BULLET)),
        destination_rect({static_cast<int>(x), static_cast<int>(y), 64, 64}),
        angleWeapon(angle),
        is_used(false),
        camera(camera),
        bullets(),
        bulles_activate(false),
        limite(10) {
    bullets = {
            BulletImage(Position{1, 2}, Position{3, 4}),
    };
}
void WeaponView::activate_bullets() {
    bulles_activate = true;
    std::cout << "BALAS ACTIVAS\n";
}
void WeaponView::draw(SDL_Renderer& renderer) {

    SDL_RenderCopyEx(&renderer, weaponTexture, nullptr, &destination_rect, angleWeapon, nullptr,
                     SDL_FLIP_NONE);

    if (bulles_activate) {
        std::cout << "------------preparando para disparar-------\n";
        SDL_SetRenderDrawColor(&renderer, 255, 255, 0, 255);  // Color amarillo para las balas
        //  for (const auto& bullet : bullets) {
        SDL_Rect bulletRect = {bullets[0].initial.x * 32, bullets[0].initial.y * 32, 5, 5};
        std::cout << "DISPARO-------\n";
        //    SDL_Rect bulletRect = {bullet.initial.x, bullet.initial.y, 5, 5}; // Tamaño de la bala
        SDL_RenderFillRect(&renderer, &bulletRect);
        //  }
        limite++;
    }
    if (limite <= 0) {
        limite = 10;
        bulles_activate = false;
    }
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
void WeaponView::shoot(std::vector<BulletImage>& bullets) {

    /*  Position bulletStart(destination_rect.x, destination_rect.y);
      Position bulletEnd(bulletStart.x + cos(angleWeapon) * 500,  bulletStart.y + sin(angleWeapon) *
      500); bullets.push_back(BulletImage(bulletStart, bulletEnd));*/

    bullets.clear();  // Borra las balas anteriores (si solo quieres una)
    Position bulletStart(destination_rect.x / 32, destination_rect.y / 32);
    Position bulletEnd(
            bulletStart.x + cos(angleWeapon) * 10,  // 10 tiles de alcance, ajusta si quieres
            bulletStart.y + sin(angleWeapon) * 10);
    bullets.push_back(BulletImage(bulletStart, bulletEnd));
    bulles_activate = true;
}

void WeaponView::updateBullets(std::vector<BulletImage>& bullets) {
    int speed = 10;
    for (auto& bullet: bullets) {
        bullet.initial.x += cos(angleWeapon) * speed;
        bullet.initial.y += sin(angleWeapon) * speed;
    }
}
