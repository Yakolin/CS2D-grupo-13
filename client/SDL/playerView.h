#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_video.h>

#include "../../common/game_image.h"
#include "../../common/game_info.h"
#include "../../common/player_command_types.h"
#include "../tipos.h"
#include "bullet.h"
#include "camera.h"
#include "gameConfig.h"
#include "manageTexture.h"
#include "renderizable.h"
#include "weaponView.h"

class PlayerView: public Renderizable {


private:
    GameConfig config;
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
    Team clave_team;
    float x_actual;
    float y_actual;
    float velocity_x;
    float velocity_y;
    Coordenada prev_pos;
    Coordenada target_pos;
    float interp_duration;
    float interp_time;
    std::unordered_map<WeaponCode, std::unique_ptr<WeaponView>> weapons;
    bool activar_weapon;
  //  SDL_Texture* texture_player;
    WeaponCode equipped_weapon;
    std::unordered_map<Team , SDL_Texture*> textures_player;

    void calcular();

    std::unordered_map<Team, SDL_Texture*> load_claves(const Skins& clave_player);
    
public:
    explicit PlayerView(const float& x, const float& y, const Skins& clave_player, const float& speed,
                        Camera* camera_reseiver, ManageTexture* manger_texture, GameConfig& config);


    void update_equip(const PlayerImage player_aux);


    void setPrevPos(const float& new_x, const float& new_y);
    void setTargetPos(const float& new_x, const float& new_y);
    ~PlayerView();
    void setInterpDuration(const float& duration);
    void add_speed(const SDL_Keycode& tecla);

    void stop_speed(const SDL_Keycode& tecla);

    void auxiliar(const SDL_Keycode& tecla);

    void update_weapons(const std::vector<WeaponImage>& weapons_vec);
    void activate_weapon();

    void draw(SDL_Renderer& renderer) override;

    void update(const float& dt);
    void update_view_angle(const int& mause_x, const int& mause_y);

    float getSpeed() const;
    std::string getRutaPlayer() const;
    int getWidthImg() const;   // todo no inicializadas
    int getHeightImg() const;  // todo no incializadas no usar
    float getAnglePlayer() const;
    void setVelX(float vx);
    void setVelY(float vy);
    float getVelX() const;
    float getVelY() const;
    void setInterpTime(const float& time);
    int pasar_pixeles_x(const float& tile_x);
    int pasar_pixeles_y(const float& tile_y);

    void setXActual(float x);
    void setYActual(float y);
    void setSpeed(float newSpeed);
    float getXActual();
    float getYActual();


};

#endif  // PLAYERVIEW_H
