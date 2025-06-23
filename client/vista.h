#ifndef VISTA_H
#define VISTA_H
#include <QApplication>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../common/game_image.h"
#include "../common/game_info.h"
#include "../common/liberror.h"
#include "../common/queue.h"
#include "../common/socket.h"
#include "Qt/menuView.h"
#include "Qt/scoreBoard.h"
#include "SDL/gameView.h"
#include "SDL/manageTexture.h"
#include "SDL/mapView.h"
#include "SDL/quit_game_exception.h"
#include "model/protocol.h"
#include "model/receiver.h"  // necesario para recibir cosas

#include "controller.h"
#include "tipos.h"

class Vista {

private:
    int& argc;
    char** argv;
    Socket skt;  // enviar referencia al controller
    ClientProtocol protocolo;
    LobbyCommandType opcionElegida;
    Player info_game;

    void init_game(SDL_Window*& ventana, SDL_Renderer*& renderer, const GameConfig& config);

    void free_components(SDL_Window* ventana, SDL_Renderer* renderer);

public:
    explicit Vista(int& argc, char* argv[]);
    bool showLobby();

    std::map<player_id_t, InfoPlayer> showGame();

    void showScoreboard(const std::map<player_id_t, InfoPlayer>& table);

    void reset();

    ~Vista();

private:
};

#endif  // VISTA_H
