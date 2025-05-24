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

    QApplication app(argc,argv);

    MenuView menu(nullptr);

    QObject::connect(&menu, &MenuView::opcionElegida, [&menu](LobbyCommandType opcion) {
        qDebug() << "Opción recibida:" << static_cast<int>(opcion);

        std::vector<std::string> nombres_de_partidas = {
        "Partida_01",
        "ZonaDeCombate",
        "SnipersOnly",
        "MisionExplosiva",
        "DueloFinal"
    };
          // protocolo.send_lobby_command(opcion);
        switch (opcion) {
            case LobbyCommandType::CREATE_GAME:
                menu.action_create();
                break;
            case LobbyCommandType::JOIN_GAME:
                menu.action_join(nombres_de_partidas);
                break;
            case LobbyCommandType::HELP_GAME:
                menu.action_help();
                break;
            case LobbyCommandType::EXIT_GAME:
                menu.action_exit();
                break;
            case LobbyCommandType::LIST_GAMES:
                menu.action_list(nombres_de_partidas);
                break;
            default:
                break;
        }
    });
    menu.show();
    app.exec();
     /// ACA EMPIEZA EL JUEGO   

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
