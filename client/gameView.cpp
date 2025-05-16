#include "gameView.h"

GameView::GameView(int& argc, char *argv[]) : app(argc, argv) ,menu(new MenuView()), seleccion(GameMenu::NONE) {
    // Constructor de la clase GameView
}

void GameView::config_windows(QWidget *ventana, const QString &text, int width, int height) {
    ventana->setWindowTitle(text);
    ventana->setStyleSheet("background-color:rgb(117, 133, 133);");
    ventana->resize(width, height);
}



QLabel* GameView::cell(const QString &text, const bool& bold) {
    QLabel *label = new QLabel(bold ? "<b>" + text + "</b>" : text);
    label->setStyleSheet("border: 1px solid black; padding: 4px;");
    label->setAlignment(Qt::AlignCenter);
    return label;
}


GameMenu GameView::run_menu( ) {

    GameMenu num = menu->run();
    app.exec();
    return num;
}

GameView::~GameView() {
    // Destructor de la clase GameView
}
