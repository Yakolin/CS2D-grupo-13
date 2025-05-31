#ifndef VISTA_H
#define VISTA_H
#include <QApplication>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "tipos.h"
#include "../common/game_image.h"
#include "../common/queue.h"
#include "../common/socket.h"
#include "Qt/menuView.h"
#include "Qt/scoreBoard.h"
#include "SDL/gameView.h"
#include "SDL/mapView.h"
#include "model/protocol.h"
#include "model/receiver.h"  // necesario para recibir cosas

#include "controller.h"

class Vista {

public:
    int& argc;
    char** argv;
    Socket skt;  // enviar referencia al controller
    ClientProtocol protocolo;
    LobbyCommandType opcionElegida;
    std::map<Object, std::string > rutas_skins;


    explicit Vista(int& argc, char* argv[]);
    void run();
    ~Vista();
private:

    void add_player_game(const LobbyCommandType& tipo) ;
};

#endif  // VISTA_H
