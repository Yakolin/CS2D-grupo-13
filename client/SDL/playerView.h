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
    explicit PlayerView(const float& x, const float& y, const std::string& rute, const float& speed,
               Camera* camera_reseiver, ManageTexture* manger_texture, GameConfig& config);
    ~PlayerView();

    void add_speed(const SDL_Keycode& tecla);

    void stop_speed(const SDL_Keycode& tecla);

    void draw(SDL_Renderer& renderer) override;

    void update(const float& delta_time) ;
    void update_view_angle(const int& mause_x, const int& mause_y);

    float getFil() const;
    float getCol() const;
    float getSpeed() const;
    std::string getRutaPlayer() const;
    int getWidthImg() const;   // todo no inicializadas
    int getHeightImg() const;  // todo no incializadas no usar
    float getAnglePlayer() const;
    void setVelX(float vx);
    void setVelY(float vy);
    float getVelX() const;
    float getVelY() const;
    int pasar_pixeles_x(const float& tile_x);
    int pasar_pixeles_y(const float& tile_y) ;

    void updatePosition(float deltaX, float deltaY);

    void updateAnimation(int fila_animacion, int columna_animacion);

    void setFil(float newFil);
    void setCol(float newCol);
    void setSpeed(float newSpeed);
    void setRutaPlayer(const std::string& nuevaRuta);

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
    float x_actual;
    float y_actual;
    float velocity_x;  // Velocity horizontal (píxeles/segundo)
    float velocity_y;  // Velocity vertical


    void calcular();

};

#endif  // PLAYERVIEW_H
