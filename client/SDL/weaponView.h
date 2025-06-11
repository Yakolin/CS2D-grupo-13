#ifndef WEAPONVIEW_H
#define WEAPONVIEW_H
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "../tipos.h"

#include "camera.h"
#include "manageTexture.h"
#include "renderizable.h"
class WeaponView: public Renderizable {
private:
    ManageTexture& manager;
    SDL_Texture* weaponTexture;
    SDL_Rect destination_rect;
    float angleWeapon;
    bool is_used;
    Camera& camera;

public:
    explicit WeaponView(Camera& camera, ManageTexture& managertexture, const WeaponCode& clave,
                        const float& x, const float& y, const float& angle);


    void draw(SDL_Renderer& renderer) override;


    void update(const int& x_player, const int& y_player, const float& angle);

    void setUsed(bool used);


    void shoot();
};


#endif  // WEAPONVIEW_H