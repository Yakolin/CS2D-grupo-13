#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include "camera.h"
#include "../tipos.h"
#include "gameConfig.h"
#include "manageTexture.h"
#include "renderizable.h"

class PlayerView: public Renderizable {
public:
    PlayerView(const float& x, const float& y, const std::string& rute, const float& speed,
               Camera* camera_reseiver, ManageTexture* manger_texture, GameConfig& config);
    ~PlayerView();

    void draw(SDL_Renderer& renderer) override;

    void update() ;
    void update_view_angle(const int& mause_x, const int& mause_y);

    float getFil() const;
    float getCol() const;
    float getSpeed() const;
    std::string getRutaPlayer() const;
    int getWidthImg() const;   // todo no inicializadas
    int getHeightImg() const;  // todo no incializadas no usar
    float getAnglePlayer() const;
    int pasar_pixeles_x(const float& tile_x);
    int pasar_pixeles_y(const float& tile_y) ;

    void setFil(float newFil);
    void setCol(float newCol);
    void setSpeed(float newSpeed);
    void setRutaPlayer(const std::string& nuevaRuta);
    void setObjetivoTiles(const float& tile_x, const float& tile_y);
    void add_speed(const SDL_Keycode& tecla);
    // void setTexturePlayer(SDL_Texture texture);

private:
    GameConfig config;
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
    Camera* camera;
    ManageTexture* manejador;
    int player_id;
    float filObjetivo;
    float colObjetivo;

    void calcular();

};

#endif  // PLAYERVIEW_H
