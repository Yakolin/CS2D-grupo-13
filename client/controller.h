#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "vista.h"

class Controller {
private:
    Vista vista;

public:
    explicit Controller();

    void run(int& argc,  char *argv[]);

};

#endif // CONTROLLER_H