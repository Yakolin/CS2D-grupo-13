#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "gameView.h"

class Controller {
private:
    GameView gameView;
public:
    explicit Controller(int& argc,  char *argv[]) ;

    void run();
};

#endif // CONTROLLER_H