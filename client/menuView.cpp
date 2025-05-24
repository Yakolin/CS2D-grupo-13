#include "menuView.h"
const int HEIGHT_MENU = 500;
const int WIDTH_MENU = 500;

#define OPCION_CREATE "Create Game"
#define OPCION_JOIN "Join Game"
#define OPCION_EXIT "Exit Game"
#define OPCION_LIST "List Game"
#define OPCION_HELP "Help Game"

MenuView::MenuView(QWidget* parent)
    : QDialog(parent),
      img_icono(new QLabel(this)),
      clicked_text(),
      botones()
{
    botones[OPCION_CREATE] = LobbyCommandType::CREATE_GAME;
    botones[OPCION_JOIN] = LobbyCommandType::JOIN_GAME;
    botones[OPCION_LIST] = LobbyCommandType::LIST_GAMES;
    botones[OPCION_EXIT] = LobbyCommandType::EXIT_GAME;
    botones[OPCION_HELP] = LobbyCommandType::HELP_GAME;

    QPixmap img_img("assets/gfx/cs2d.png");
    img_icono->setPixmap(img_img);

    setWindowTitle("Counter Strike");
    resize(WIDTH_MENU, HEIGHT_MENU);


    QVBoxLayout* layout = new QVBoxLayout(this);  // <== el this es clave
    layout->addWidget(img_icono, 0, Qt::AlignCenter);


    add_button(layout, OPCION_CREATE);
    add_button(layout, OPCION_JOIN);
    add_button(layout, OPCION_HELP);
    add_button(layout, OPCION_EXIT);
    add_button(layout, OPCION_LIST);
}

void MenuView::action_create() {

    LobbyView* lobby = new LobbyView();
    lobby->action_create();
    lobby->show();
}

void MenuView::action_join(std::vector<std::string>& list) {

    LobbyView* lobby = new LobbyView();
    lobby->action_join(list);
    lobby->show();
}

void MenuView::action_list(const std::vector<std::string>& list) {
    LobbyView* lobby = new LobbyView();
    lobby->action_list(list);
    lobby->show();
}

void MenuView::action_exit() {
    QMessageBox::StandardButton answer = QMessageBox::question(nullptr, "Mensaje", "Desea salir?");
    if (answer == QMessageBox::Yes) {
        close();
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

    msgBox.exec();
}




void MenuView::add_button(QVBoxLayout* layout, const QString& text) {
    QPushButton* button = new QPushButton(text);
    button->setFixedSize(200, 50);

    QObject::connect(button, &QPushButton::clicked, [this, button]() {
        clicked_text = button->text();
        emit opcionElegida(getCommantType());
    });

    layout->addWidget(button, 0, Qt::AlignHCenter);
}


LobbyCommandType MenuView::getCommantType() const {
    if (botones.find(clicked_text) != botones.end()) {
        return botones.at(clicked_text);
    }
    return LobbyCommandType::NONE;
}

MenuView::~MenuView() {}

