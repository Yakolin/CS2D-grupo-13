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
#include "model/receiver.h"  // necesario para recibir cosas
#include "../common/socket.h" 
#include "../common/game_image.h"
#include "model/protocol.h"
#include "controller.h"
#include "gameView.h"
#include "mapView.h"
#include "menuView.h"
#include "scoreBoard.h"

class Vista {

public:

    int& argc;
    char** argv;
    Socket skt; // enviar referencia al controller
    Queue<GameImage> deque;
    Receiver receiver;
    Controller controller;
    ClientProtocol protocolo;


    explicit Vista(int& argc, char* argv[]);
    void run();
    ~Vista();
};

#endif  // VISTA_H
