#include "vista.h"
#include <QApplication>
#include <QStackedWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTabWidget>

Vista::Vista(int& argc, char* argv[])
    : argc(argc), argv(argv), skt(argv[1], argv[2]), protocolo(skt),opcionElegida(LobbyCommandType::NONE
    ) {}


void Vista::manejarOpcionElegida(const LobbyCommandType& tipo) {
    if (tipo == LobbyCommandType::CREATE_GAME) {
        // Crear vista de juego
    } else if (tipo == LobbyCommandType::JOIN_GAME) {
        // Entrar al juego
    }
}



void Vista::run() {

    QApplication app(argc, argv);  
    MenuView menu(nullptr,protocolo);
    menu.show();

    QObject::connect(&menu, &MenuView::opcionElegida, [this,&menu](LobbyCommandType tipo){
        this->opcionElegida = tipo;
        qDebug() << "Opción recibida:" << static_cast<int>(tipo);
        menu.close();
    });
    app.exec();
    
    
    if(opcionElegida != LobbyCommandType::CREATE_GAME && opcionElegida != LobbyCommandType::JOIN_GAME){
        return;
    }
    
    try {
        GameView gameView(std::move(skt), 500, 500);
        gameView.draw_game();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

Vista::~Vista() {}
