#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "gameView.h"
#include "mapView.h"
#include <vector>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>       
#include <sstream>       
#include <vector>
#include <stdexcept>  
class Controller {
private:
    GameView gameView;

    std::vector<std::vector<char>> cargar_mapa(const std::string& archivo) ;
public:
    explicit Controller(int& argc,  char *argv[]) ;

    void run();
};

#endif // CONTROLLER_H