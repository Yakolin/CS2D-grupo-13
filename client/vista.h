#ifndef VISTA_H
#define VISTA_H
#include "controller.h"
#include "gameView.h"
#include "mapView.h"
#include "menuView.h"
#include "scoreBoard.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>       
#include <sstream>       
#include <stdexcept>  
#include <QApplication>

class Vista {

public:
    Controller controller;
    GameView gameView;
    QApplication app;
    std::vector<std::vector<char>> cargar_mapa(const std::string& archivo) ;

    explicit Vista(int& argc,  char *argv[]);
    void run();
    ~Vista();
};

#endif // VISTA_H