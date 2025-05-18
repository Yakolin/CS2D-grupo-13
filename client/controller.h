#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "playerView.h"
#include "gameView.h"
#include "mapView.h"
#include "menuView.h"
#include "scoreBoard.h"
#include <vector>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>       
#include <sstream>       
#include <vector>
#include <stdexcept>  
#include <QApplication>
class Controller {
private:
    GameView gameView;
    QApplication app;
    GameMenu seleccion;

    std::vector<std::vector<char>> cargar_mapa(const std::string& archivo) ;
public:
    explicit Controller(int& argc,  char *argv[]) ;

    void run();
};

#endif // CONTROLLER_H