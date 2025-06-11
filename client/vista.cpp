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
    std::cout << "Mapa: " << info_game.map << std::endl;

    if (opcionElegida != LobbyCommandType::CREATE_GAME &&
        opcionElegida != LobbyCommandType::JOIN_GAME) {
        return;
    }
    GameInfo info_game = protocolo.read_game_info();
    std::vector<Position> walls = info_game.map_info.walls;
    std::cout << "walls ===================== " << std::endl;
    std::cout << "cant walls ====== " << walls.size() << std::endl;
    Acknowledge ack = Acknowledge::READY;
    protocolo.send_acknowledge(ack);  // tal vez esto se tenga que mandar luego de
                                      // chequear que game info esta bien
    try {
        GameView gameView(std::move(skt));
        if (!gameView.init_game())
            throw std::runtime_error(std::string("Error a inicializar game"));


        if (opcionElegida == LobbyCommandType::CREATE_GAME) {
            if (!gameView.add_player(11, 4, 200.0f, "assets/gfx/terrorist/t2.png")) {
                return;
            }
        } else {
            if (!gameView.add_player(23, 9, 200.0f, "assets/gfx/terrorist/t2.png")) {
                return;
            }
        }
        gameView.draw_game(walls);
    } catch (const std::exception& e) {
        std::cerr << "Excepción atrapada en vista: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Excepción desconocida en vista " << std::endl;
    }
}

Vista::~Vista() {}
