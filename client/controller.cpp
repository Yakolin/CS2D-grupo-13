#include "controller.h"

Controller::Controller() : vista() {}  //! a consultar , cada cliente no deberia tener una vista propia sino todos la misma referencia a la vista

void Controller::run(int& argc,  char *argv[]) {
    vista.run(argc, argv);
}