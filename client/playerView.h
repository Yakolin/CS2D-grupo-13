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

    void draw_player(SDL_Renderer* renderer,SDL_Texture* tiles);

    void add_speed(const SDL_Keycode& tecla);
    
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
    SDL_Rect* origin_rect;
    SDL_Rect destination_rect;
    float speed_player;
   // SDL_Texture texture_player;

    int pasar_pixeles(const float& pos);

};

#endif // PLAYERVIEW_H