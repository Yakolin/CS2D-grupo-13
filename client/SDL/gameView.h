#ifndef GAME_VIEW_H
#define GAME_VIEW_H
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include "../../common/game_image.h"
#include "../controller.h"
#include "../tipos.h"
#include "camera.h"
#include "manageTexture.h"
#include "mapView.h"
#include "playerView.h"
#include "renderizable.h"
#include <stdexcept> 
#include "gameConfig.h"
class GameView {

private:
    GameConfig config;
    Controller controller;
    std::map<char, std::string> leyenda;
    std::map<char, Object> ids;
    SDL_Window* ventana;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    PlayerView* player;
    Camera camera;
    ManageTexture manger_texture;
    std::map<player_id_t, PlayerView*> players; 
    GameImage snapshot;



    bool handle_events(const SDL_Event& evento);

    void load_textures();

    void update_status_game();

    void draw_players();


public:
    explicit GameView(Socket&& skt);

    bool cargar_skins(const std::map<Object, std::string >& rutas_skins);

    /*
    pre:  width y height deben ser mayores que 0.
    post: devuelve true si la unicializacion salio bien de ventana y renderer.
    */
    bool init_game();
    /*
    pre:
    post:
    */
    void draw_game();

    bool add_player(float x, float y ,int speed, const std::string& img );

    void start();


    ~GameView();
};

#endif  // GAME_VIEW_H
