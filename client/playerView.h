#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H
#include <iostream>
#include "tipos.h"
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include <map>

class PlayerView {
public:
    PlayerView(const float& x , const float& y, const std::string rute, const float& speed);
    ~PlayerView();

    void draw_player(SDL_Renderer* renderer,SDL_Texture* tiles,const  MedidasSprites& sprite);

    void add_speed(const SDL_Keycode& tecla);

    void update_view_angle(const int& mause_x,const int& mause_y);
    
    float getFil() const;
    float getCol() const;
    float getSpeed() const;
    std::string getRutaPlayer() const;

    void setFil(float newFil);
    void setCol(float newCol);
    void setSpeed(float newSpeed);
    void setRutaPlayer(const std::string& nuevaRuta);
   // void setTexturePlayer(SDL_Texture texture);

private:
    float fil;
    float col;
    std::string rutaPlayer;
    SDL_Rect origin_rect;
    SDL_Rect destination_rect;
    float speed_player;
    int width_img;
    int height_img;
    ItemSprite spritePlayer;
    ItemSprite item;
    float anglePlayer;

   // SDL_Texture texture_player;

    int pasar_pixeles(const float& pos);

};

#endif // PLAYERVIEW_H