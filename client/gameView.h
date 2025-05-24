#ifndef GAME_VIEW_H
#define GAME_VIEW_H
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>

#include "../common/game_image.h"
#include "../common/queue.h"
#include "model/client_action.h"
#include "model/receiver.h"

#include "controller.h"
#include "manageTexture.h"
#include "mapView.h"
#include "playerView.h"
#include "renderizable.h"
#include "tipos.h"

#define MAX_QUEUE_SIZE 100000

class GameView {

private:
    Socket socket;
    std::shared_ptr<Queue<std::unique_ptr<InterfaceClientAction>>> send_queue;
    std::shared_ptr<Queue<GameImage>> recv_queue;
    Receiver receiver;
    Sender sender;
    Controller controller;
    std::map<char, std::string> leyenda;
    std::map<char, Objet> ids;
    SDL_Window* ventana;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    PlayerView* player;
    SDL_Rect camera;
    ManageTexture manger_texture;
    int width;
    int height;


    void add_player(PlayerView& player);

    bool handle_events(const SDL_Event& evento);

    std::vector<std::vector<char>> cargar_mapa(const std::string& archivo);

    void load_textures();


public:
    explicit GameView(Socket&& skt, const int& width_reseiver, const int& height_reseiver);

    /*
    pre:  width y height deben ser mayores que 0.
    post: devuelve true si la unicializacion salio bien de ventana y renderer.
    */
    bool init_render_window();

    void draw_game();


    ~GameView();
};

#endif  // GAME_VIEW_H
