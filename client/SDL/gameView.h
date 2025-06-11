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
#include "bomb.h"
#include "../../common/constant_rate_loop.h"
#include "../../common/game_image.h"
#include "../controller.h"
#include "../tipos.h"

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
    std::map<char, std::string> leyenda;
    std::map<TextView, std::string> texts;
    std::map<char, Object> ids;
    SDL_Window* ventana;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
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
    bool activa;

    bool bomb_activate;

    bool handle_events(const SDL_Event& evento);

    void load_textures();


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
    void draw_game(const std::vector<Position> walls);

    bool add_player(float x, float y, int speed, const std::string& img);

    void start();

    void reset_values(PlayerView* player, const float& x_pixeles, const float& y_pixeles);


    ~GameView();
};

#endif  // GAME_VIEW_H
