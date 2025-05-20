#include "menuView.h"
const int HEIGHT_MENU = 500;
const int WIDTH_MENU = 500;

MenuView::MenuView():
        window(new QMainWindow(nullptr)),
        img_icono(new QLabel()),
        info_game(),
        clicked_text(),
        botones() {
    botones["create game"] = GameMenu::CREATE;
    botones["join game"] = GameMenu::JOIN;
    botones["help"] = GameMenu::HELP;
    botones["exit"] = GameMenu::EXIT;

    QPixmap img_img("../assets/gfx/cs2d.png");
    img_icono->setPixmap(img_img);
    window->setStyleSheet("background-color:rgb(92, 95, 95);");
    window->setWindowTitle("Counter Strike");
    window->resize(500, 500);
}

void MenuView::action_create() {
    LobbyView* lobby = new LobbyView();
    lobby->action_create();
    lobby->show();
}


void MenuView::action_join() {
    QMessageBox::information(nullptr, "Mensaje", "Se unió a una partida");
}

void MenuView::action_exit() {
    QMessageBox::StandardButton answer = QMessageBox::question(nullptr, "Mensaje", "Desea salir?");
    if (answer == QMessageBox::Yes) {
        window->close();
    }
}

void MenuView::action_help() {

    QString ayuda = "<b>create game</b><br>"
                    "para crear una nueva partida<br>"
                    "<b>join game</b><br>"
                    "para unirse a una partida existente<br>"
                    "<b>exit</b><br>"
                    "para salir";
    QMessageBox msgBox;
    msgBox.setWindowTitle("Help");
    msgBox.setText(ayuda);

    msgBox.setStyleSheet("background-color:rgb(90, 94, 94); color: black");

    msgBox.exec();
}


void MenuView::add_button(QVBoxLayout* layout, const QString& text) {
    QPushButton* button = new QPushButton(text);
    button->setFixedSize(200, 50);

    QObject::connect(button, &QPushButton::clicked, [this, button]() {
        clicked_text = button->text();
        // Podés hacer una acción asociada, por ejemplo:
        // qDebug() << "Botón clickeado:" << clicked_text;
        if (clicked_text == "create game")
            action_create();
        else if (clicked_text == "join game")
            action_join();
        else if (clicked_text == "Help")
            action_help();
        else if (clicked_text == "exit game")
            action_exit();
    });

    layout->addWidget(button, 0, Qt::AlignHCenter);
}


GameMenu MenuView::run() {
    // GameMenu election;

    QWidget* central = new QWidget(window);
    window->setCentralWidget(central);
    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(img_icono, 0, Qt::AlignCenter);
    add_button(layout, "create game");
    add_button(layout, "join game");
    add_button(layout, "Help");
    add_button(layout, "exit game");

    central->setLayout(layout);
    window->show();


    if (!clicked_text.isEmpty()) {
        return botones[clicked_text];
    }
    return GameMenu::NONE;
}
MenuView::~MenuView() {}

/*void GameView::config_windows(QWidget *ventana, const QString &text, int width, int height) {
    ventana->setWindowTitle(text);
    ventana->setStyleSheet("background-color:rgb(37, 135, 40);");
    ventana->resize(width, height);
}



QLabel* GameView::cell(const QString &text, const bool& bold) {
    QLabel *label = new QLabel(bold ? "<b>" + text + "</b>" : text);
    label->setStyleSheet("border: 1px solid black; padding: 4px;");
    label->setAlignment(Qt::AlignCenter);
    return label;
}
*/
