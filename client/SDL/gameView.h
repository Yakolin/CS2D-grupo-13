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
#include "managerEvent.h"
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
#include "bombTimer.h"
class GameView {

private:
    GameConfig& config;
    SoundConfig config_sound;
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
    ManagerEvent events;
    BombTimer bomba_timer;

    void draw_timer_bomb();

    void delete_players_death();


    void update_mouse_hold();

    void update_bullets_snapshot();

    void update_status_game();

    void draw_players();

    void step();

    bool should_keep_running();

    void process_events();

    void update_game();

    bool update_game_image();

    void render_game();

    void update_sounds(const PlayerImage& player);


    /*
    INPUT HANDLER
    */
    void send_burst();

    Skins load_claves(const Player& info_Player);

    /* sonud handeler */
    void handle_bomb_sound();

    void handle_state_game();

public:
    explicit GameView(Socket& skt, const GameInfo& game_info, const Player& info_game,
                      SDL_Window* ventana, SDL_Renderer* renderer, ManageTexture& manger_texture,
                      GameConfig& config);


    void run();

    void reset_values(PlayerView* player, const float& x_pixeles, const float& y_pixeles);

    std::map<player_id_t, InfoPlayer> get_info_players_map();

    ~GameView();
};

#endif  // GAME_VIEW_H
