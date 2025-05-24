#ifndef VISTA_H
#define VISTA_H
#include <QApplication>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../common/game_image.h"
#include "../common/queue.h"
#include "../common/socket.h"
#include "model/protocol.h"
#include "model/receiver.h"  // necesario para recibir cosas

#include "controller.h"
#include "SDL/gameView.h"
#include "SDL/mapView.h"
#include "Qt/menuView.h"
#include "Qt/scoreBoard.h"

class Vista {

public:
    int& argc;
    char** argv;
    Socket skt;  // enviar referencia al controller
    ClientProtocol protocolo;


    explicit Vista(int& argc, char* argv[]);
    void run();
    ~Vista();
};

#endif  // VISTA_H
