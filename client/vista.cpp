#include "vista.h"

Vista::Vista(int& argc, char* argv[]) :
    argc(argc),
    argv(argv),
    skt(argv[1],argv[2]),
    deque(),
    receiver(skt, deque),
    controller(skt)
{}


void Vista::run() {
   // QApplication app(argc,argv);

    //GameView gameView(receiver, controller, 500, 500);
    //GameView gameView(receiver, controller, 500, 500);
    // MenuView menu;  //libpng warning: iCCP: known incorrect sRGB profile
    // GameMenu num = menu.run(); // no es un problema peor la imagen esta corrupta //todo editarla
    // ScoreBoard table; // funciona
    // table.show_scores_game(); // funciona //todo agregar actualizacion , dejar de harcodear
    //--------------------------------------------------------------------------------------------------
    //gameView.draw_game();

    // app.exec();
}
Vista::~Vista() {}
