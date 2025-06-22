#ifndef GAME_VIEW_H
#define GAME_VIEW_H
#include <fstream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_ttf.h>

#include "../../common/constant_rate_loop.h"
#include "../../common/game_image.h"
#include "../controller.h"
#include "../soundConfig.h"
#include "../tipos.h"

#include "HUD.h"
#include "bomb.h"
#include "bullet.h"
#include "camera.h"
#include "fieldOfView.h"
#include "gameConfig.h"
#include "manageTexture.h"
#include "mapView.h"
#include "playerView.h"
#include "quit_game_exception.h"
#include "renderizable.h"
#include "shopping.h"
#include "text.h"


#define HOLD_THRESHOLD_MS 200
#define BURST_INTERVALS_MS 100

using hold_mouse_t = std::uint32_t;

class GameView {

private:
    SoundConfig config_sound;
    GameConfig& config;
    Controller controller;
    ConstantRateLoop constant_rate_loop;
    SDL_Window* ventana;
    SDL_Renderer* renderer;
    Camera camera;
    ManageTexture& manger_texture;
    PlayerView* player;
    std::map<player_id_t, PlayerView*> players;
    GameImage snapshot;
    MapView* map;
    Uint32 lastTime;
    FieldOfView* fov;
    Shopping shop;
    Bomb* bomba;
    HUD hud;
    std::vector<Bullet> bullets;
    bool activa;
    bool bomb_activate;
    std::atomic<bool> keep_running;
    bool left_mouse_pressed;
    hold_mouse_t mouse_press_start_time;
    hold_mouse_t last_burst_time;
    int press_start_x, press_start_y;
    bool blocking_mouse_motion;


    void handle_equip_type(const SDL_Keycode& tecla);

    void mouse_position_tiles(int& posx, int& posy, const int& mousex, const int& mousey);

    void update_mouse_hold();

    void handle_events(const SDL_Event& evento);

    void handle_sprite_mouse(const int& mousex, const int& mousey);

    void update_bullets_snapshot();

    void update_status_game();

    void draw_players();

    void step();

    bool should_keep_running();

    void process_events();

    void update_game();

    bool update_game_image();

    void render_game();

    void update_window();

    void update_sounds(const PlayerImage& player);


    /*
    INPUT HANDLER
    */
    void send_burst();
    void handle_single_left_click(int mouseX, int mouseY);
    void handle_key_down(SDL_Keycode& tecla);
    void handle_extras(SDL_Keycode& tecla);
    void handle_movements(SDL_Keycode& tecla);
    Skins load_claves(const Player& info_Player);

    /* sonud handeler */
    void handle_bomb_sound();

    void handle_state_game();

public:
    explicit GameView(Socket& skt, const GameInfo& game_info, const Player& info_game,
                      SDL_Window* ventana, SDL_Renderer* renderer, ManageTexture& manger_texture,
                      GameConfig& config);

    /*
    pre:
    post:
    */
    void start(const GameInfo& info_game_view);

    void run();

    void reset_values(PlayerView* player, const float& x_pixeles, const float& y_pixeles);

    std::map<player_id_t, InfoPlayer> get_info_players_map();

    ~GameView();
};

#endif  // GAME_VIEW_H
