#include "vista.h"

Vista::Vista(int& argc,  char *argv[]):
    //receiver(),
    controller(),
    gameView(&controller,500,500), 
    app(argc,argv)
    {}

    
void Vista::run() {
    
    //MenuView menu;  //libpng warning: iCCP: known incorrect sRGB profile 
    //GameMenu num = menu.run(); // no es un problema peor la imagen esta corrupta //todo editarla
    //ScoreBoard table; // funciona
    //table.show_scores_game(); // funciona //todo agregar actualizacion , dejar de harcodear
//--------------------------------------------------------------------------------------------------
    gameView.draw_game();
    
    //app.exec(); 

}
Vista::~Vista() {}