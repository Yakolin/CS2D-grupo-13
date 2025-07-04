#ifndef MANAGEREVENT_H
#define MANAGEREVENT_H
#include <map>

#include <SDL2/SDL.h>

#include "../../common/constant_rate_loop.h"
#include "../../common/game_image.h"
#include "../../common/socket.h"
#include "../controller.h"
#include "../soundConfig.h"
#include "../tipos.h"

#include "HUD.h"
#include "bomb.h"
#include "bullet.h"
#include "camera.h"
#include "fieldOfView.h"
#include "gameConfig.h"
#include "managerEvent.h"
#include "mapView.h"
#include "playerView.h"
#include "quit_game_exception.h"
#include "renderizable.h"
#include "shopping.h"
#include "text.h"
using hold_mouse_t = std::uint32_t;
class ManagerEvent {

private:
    Controller& controller;
    GameConfig& config;
    Camera& camera;
    PlayerView& player;
    std::map<player_id_t, PlayerView*>& players;
    GameImage& snapshot;
    MapView& map;
    FieldOfView& fov;
    Shopping& shop;
    Bomb& bomba;
    HUD& hud;
    std::atomic<bool>& keep_running;
    bool left_mouse_pressed;
    hold_mouse_t mouse_press_start_time;
    hold_mouse_t last_burst_time;
    int press_start_x, press_start_y;
    bool blocking_mouse_motion;
    SoundConfig& config_sound;
    ManageTexture& manger_texture;

    void send_burst();

    void handle_single_left_click(int mouseX, int mouseY);

    void handle_key_down(SDL_Keycode& tecla);

    void handle_extras(SDL_Keycode& tecla);

    void handle_movements(SDL_Keycode& tecla);

    void handle_sprite_mouse(const int& mousex, const int& mousey);

    void handle_equip_type(const SDL_Keycode& tecla);

    void update_window();

    void mouse_position_tiles(int& posx, int& posy, const int& mousex, const int& mousey);

public:
    explicit ManagerEvent(Controller& controller, GameConfig& config, Camera& camera,
                          PlayerView& player, std::map<player_id_t, PlayerView*>& players,
                          GameImage& snapshot, MapView& map, FieldOfView& fov, Bomb& bomba,
                          Shopping& shop, HUD& hud, std::atomic<bool>& keep_running,
                          SoundConfig& sound, ManageTexture& manger_texture);

    void stop();

    void start();

    void update_mouse_hold();

    void handle_events(const SDL_Event& evento);
};


#endif  // MANAGEREVENT_H
