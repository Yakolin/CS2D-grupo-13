#include "vista.h"

Vista::Vista(int& argc, char* argv[]):
        argc(argc), argv(argv), skt(argv[1], argv[2]), protocolo(skt) {}


void Vista::run() {

    QApplication app(argc, argv);

    MenuView menu(nullptr, protocolo);
    LobbyCommandType resultado = LobbyCommandType::NONE;

    QObject::connect(&menu, &MenuView::opcionElegida, [this, &menu, &resultado](LobbyCommandType opcion) {
                qDebug() << "Opción recibida:" << static_cast<int>(opcion);

                std::vector<std::string> nombres_de_partidas = {"Partida_01", "ZonaDeCombate",
                                                                "SnipersOnly", "MisionExplosiva",
                                                                "DueloFinal"};
                protocolo.send_lobby_command(opcion);
                resultado = opcion;
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
                       // std::vector<std::string> games_names = protocolo.
                        menu.action_list(nombres_de_partidas);
                        break;
                    default:
                        break;
                }
            });
    menu.show();
    app.exec();
    menu.close();
    /// ACA EMPIEZA EL JUEGO

    if (resultado == LobbyCommandType::CREATE_GAME || resultado == LobbyCommandType::JOIN_GAME) {
        try{          
            GameView gameView(std::move(skt), 500, 500);
            gameView.start();
            gameView.draw_game();
        }catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
    }

    // ScoreBoard table; // funciona
    // table.show_scores_game(); // funciona //todo agregar actualizacion , dejar de harcodear
    // app.exec();
}
Vista::~Vista() {}
