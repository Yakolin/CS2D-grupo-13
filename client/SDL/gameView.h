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
#include "../tipos.h"
#include "bullet.h"
#include "HUD.h"
#include "bomb.h"
#include "camera.h"
#include "fieldOfView.h"
#include "gameConfig.h"
#include "manageTexture.h"
#include "mapView.h"
#include "playerView.h"
#include "renderizable.h"
#include "shopping.h"
#include "text.h"
class GameView {

private:
    GameConfig config;
    Controller controller;
    std::map<TextView, std::string> texts;
    SDL_Window* ventana;
    SDL_Renderer* renderer;
    PlayerView* player;
    Camera camera;
    ManageTexture manger_texture;
    std::map<player_id_t, PlayerView*> players;
    GameImage snapshot;
    MapView* map;
    Uint32 lastTime;
    FieldOfView* fov;
    Shopping shop;
    Bomb* bomba;
    HUD hud;
    bool activa;
    std::vector<Bullet> bullets;

    bool bomb_activate;
    void handle_equip_type(const SDL_Keycode& tecla);
    void mouse_position_tiles(int& posx, int& posy , const int& mousex, const int& mousey);
    bool handle_events(const SDL_Event& evento);


    void update_status_game();

    void draw_players();


public:
    explicit GameView(Socket&& skt);

    SDL_Window* init_window(const GameConfig& config);

    SDL_Renderer* init_renderer(SDL_Window* window, GameConfig& config);

    /*
    pre:  width y height deben ser mayores que 0.
    post: devuelve true si la unicializacion salio bien de ventana y renderer.
    */
    bool init_game();
    /*
    pre:
    post:
    */
    void initial_draw_game(const GameInfo& info_game_view /*, const Player& info_game*/);
    void draw_game();

    bool add_player(float x, float y, int speed, const Claves_skins& claves);

    void start();

    void reset_values(PlayerView* player, const float& x_pixeles, const float& y_pixeles);


    ~GameView();
};

#endif  // GAME_VIEW_H
