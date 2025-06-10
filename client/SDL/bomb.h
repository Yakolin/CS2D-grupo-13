#ifndef BOMB_H
#define BOMB_H
#include <iostream>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>

#include "../tipos.h"

#include "camera.h"
#include "gameConfig.h"
#include "manageTexture.h"
#include "playerView.h"
#include "renderizable.h"

class Bomb: public Renderizable {

private:
    PlayerView& player_actual;
    GameConfig& config;
    Camera& camera;
    ManageTexture& manejador;
    int width_img;
    int height_img;
    SDL_Rect origin_rect;
    SDL_Rect destination_rect;
    Coordenada item_sprite;
    Coordenada pos_bomb;
    int angle;
    bool activada;

    void update();

public:
    explicit Bomb(PlayerView& plaayer, Camera& camera_reseiver, ManageTexture& manejador,
                  GameConfig& config);
    ~Bomb();

    void draw(SDL_Renderer& renderer) override;

    bool get_activate() const;
};

#endif  // BOMB_H
