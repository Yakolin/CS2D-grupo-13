#ifndef WEAPONVIEW_H
#define WEAPONVIEW_H
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "camera.h"
#include "game_image.h"
#include "manageTexture.h"
#include "renderizable.h"
#include "tipos.h"
class WeaponView: public Renderizable {
private:
    ManageTexture& manager;
    SDL_Texture* weaponTexture;
    //   SDL_Texture* bullet_texture;
    SDL_Rect destination_rect;
    float angleWeapon;
    bool is_used;
    Camera& camera;
    std::vector<BulletImage> bullets;
    bool bulles_activate;
    int limite;

public:
    explicit WeaponView(Camera& camera, ManageTexture& managertexture, const Weapon& clave,
                        const float& x, const float& y, const float& angle);

    void activate_bullets();

    void draw(SDL_Renderer& renderer) override;


    void update(const int& x_player, const int& y_player, const float& angle);

    void setUsed(bool used);

    bool getUsed();

    void shoot(std::vector<BulletImage>& bullets);
    void updateBullets(std::vector<BulletImage>& bullets);
};

#endif  // WEAPONVIEW_H