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
    GameConfig& config;
    Camera& camera;
    ManageTexture& manejador;
    SDL_Texture* texture_bomb;
    SDL_Texture* texture_explosion;
    int width_img;
    int height_img;
    SDL_Rect origin_rect;
    SDL_Rect destination_rect;
    CoordenadaInt item_sprite;
    Coordenada pos_bomb;
    int angle;
    bool activada;
    int last_frame_time;
    BombState state;
    int x;
    int y;


    void draw_dropped(SDL_Renderer& renderer);

    void draw_activate(SDL_Renderer& renderer);

public:
    explicit Bomb(int x, int y, Camera& camera_reseiver, ManageTexture& manejador,
                  GameConfig& config);
    bool explosion_finished();
    ~Bomb();

    void draw(SDL_Renderer& renderer) override ;

    void set_pos(int& new_x, int& new_y);

    void update_bomb(const BombImage& bombImg);

};

#endif  // BOMB_H
