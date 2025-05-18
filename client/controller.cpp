#include "controller.h"


Controller::Controller(int& argc,  char *argv[]) : 
            gameView(500,500), 
            app(argc,argv), 
            seleccion(GameMenu::NONE) 
            {}



void Controller::run() {
    //MenuView menu;  //libpng warning: iCCP: known incorrect sRGB profile 
    //GameMenu num = menu.run(); // no es un problema peor la imagen esta corrupta //todo editarla
    //ScoreBoard table; // funciona
    //table.show_scores_game(); // funciona //todo agregar acutualizacion , dejar de harcodear
//--------------------------------------------------------------------------------------------------
   // GameView game( 38*32,17*32);
    gameView.draw_game();
    
    //app.exec(); // todo mantener qt activo durante toda la ejecusion

}