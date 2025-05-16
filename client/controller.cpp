#include "controller.h"

Controller::Controller(int& argc,  char *argv[]) : gameView(argc, argv) {}

void Controller::run() {
    // gameView.run_menu();
    MapView map;
    map.start_game();

}