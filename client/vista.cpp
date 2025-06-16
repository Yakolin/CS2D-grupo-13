#include "vista.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QTabWidget>
#include <QVBoxLayout>

Vista::Vista(int& argc, char* argv[]):
        argc(argc),
        argv(argv),
        skt(argv[1], argv[2]),
        protocolo(skt),
        opcionElegida(LobbyCommandType::NONE),
        info_game() {}


void Vista::run() {

    QApplication app(argc, argv);
    MenuView menu(nullptr, protocolo);
    menu.show();

    QObject::connect(&menu, &MenuView::opcionElegida,
                     [this, &menu](LobbyCommandType tipo, Player info) {
                         this->opcionElegida = tipo;
                         this->info_game = info;
                         menu.close();
                     });
    app.exec();
    std::cout << "Nombre del jugador: " << info_game.info.name_player << std::endl;
    std::cout << "Nombre del juego: " << info_game.info.name_game << std::endl;
    std::cout << "Equipo: " << info_game.team << std::endl;
    std::cout << "Skin: " << info_game.skin << std::endl;
    std::cout << "Skin2: " << info_game.skin2 << std::endl;
    std::cout << "Mapa: " << info_game.map << std::endl;

    if (opcionElegida != LobbyCommandType::CREATE_GAME &&
        opcionElegida != LobbyCommandType::JOIN_GAME) {
        return;
    }
    GameInfo info_game_view = protocolo.read_game_info();
    Acknowledge ack = Acknowledge::READY;
    protocolo.send_acknowledge(ack);  // tal vez esto se tenga que mandar luego de
                                      // chequear que game info esta bien
    try {
        GameView gameView(std::move(skt),info_game_view,info_game);
    std::cout << "inicalizado correctamente " << info_game.map << std::endl;
        if (!gameView.init_game())
            throw std::runtime_error(std::string("Error a inicializar game"));
    std::cout << "cargaron objetos " << info_game.map << std::endl;

        gameView.start(info_game_view );
    std::cout << "strat " << info_game.map << std::endl;

        gameView.run();
    } catch (const QuitGameException& e) {  // no pongo mensaje porque es el comportamiento esperado
    } catch (const LibError& e) {           // no pongo mensaje porque es el comportamiento esperado
    } catch (const std::exception& e) {
        std::cerr << "Excepción atrapada en vista: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Excepción desconocida en vista " << std::endl;
    }
}

Vista::~Vista() {}
