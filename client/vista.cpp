#include "vista.h"

Vista::Vista(int& argc,  char *argv[]):
    //receiver(),
    controller(), 
    app(argc,argv)
    {}

    
void Vista::run() {
    
    MenuView menu;  //libpng warning: iCCP: known incorrect sRGB profile 
    menu.run(); //o es un problema peor la imagen esta corrupta //todo editarla
    //ScoreBoard table; // funciona
    //table.show_scores_game(); // funciona //todo agregar actualizacion , dejar de harcodear
//--------------------------------------------------------------------------------------------------
    //GameView gameView(&controller,500,500);
    //gameView.draw_//game();
    
    app.exec(); 

}
Vista::~Vista() {}