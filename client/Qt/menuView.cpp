#include "menuView.h"
const int HEIGHT_MENU = 500;
const int WIDTH_MENU = 500;

#define OPCION_CREATE "Create Game"
#define OPCION_PLAY "Play"
#define OPCION_JOIN "Join Game"
#define OPCION_EXIT "Exit Game"
#define OPCION_LIST "List Game"
#define OPCION_HELP "Help Game"
#define OPCION_MENU "Back"

MenuView::MenuView(QWidget* parent, ClientProtocol& protocol):
        QWidget(parent), stack(this), menu(), lobby(*this, protocol), protocol(protocol) {

    // Icono del CS2D
    menu.setWindowTitle("Counter Strike 2D - Grupo 13");
    resize(WIDTH_MENU, HEIGHT_MENU);
    // Layout principal seria este, en el que todo lo demas se va a posar.
    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->addWidget(&stack);
    setLayout(main_layout);

    // Esta layout es para los botones de play y exit
    QVBoxLayout* menu_layout = new QVBoxLayout(&menu);
    add_buttons_menu(menu_layout);
    main_layout->addLayout(menu_layout);
    QTabWidget* page_play = new QTabWidget();
    page_play->setStyleSheet(PAGE_PLAY_STYLE);
    // Estos son los botones de volver aca, al menu
    // Esto hay que tener cuidado, debe estar en orden, quiza una variable global
    // seria mejor
    stack.addWidget(&menu);
    stack.addWidget(page_play);
    lobby.play_game(page_play);
    connect(&lobby, &LobbyView::opcionElegida, this, &MenuView::opcionElegida);
    // Sonido
    start_music();
}
void MenuView::start_music() {
    this->music = new QMediaPlayer(this);
    this->playlist = new QMediaPlaylist(this);
    QString path = QDir::current().absoluteFilePath("assets/sfx/menu.wav");
    QUrl url = QUrl::fromLocalFile(path);
    playlist->addMedia(url);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music->setPlaylist(playlist);
    music->setVolume(15);
    music->play();
}
void MenuView::add_buttons_menu(QVBoxLayout* menu_layout) {
    QVBoxLayout* buttons_layout = new QVBoxLayout();
    QLabel* img_icono = new QLabel();
    QPixmap img_img("assets/gfx/cs2d.png");
    img_icono->setPixmap(img_img);

    // Aca los botones
    buttons_layout->addWidget(img_icono, 0, Qt::AlignCenter);
    buttons_creator.add_button(buttons_layout, OPCION_PLAY, [this]() { this->action_play(); });
    buttons_creator.add_button(buttons_layout, OPCION_EXIT, [this]() { this->action_exit(); });

    QWidget* container = new QWidget();
    container->setLayout(buttons_layout);
    QVBoxLayout* v_layout = new QVBoxLayout();
    v_layout->addStretch();
    // Aca , una vez metido en el v_layout, lo pones a la izquierda
    v_layout->addWidget(container, 0, Qt::AlignLeft);
    menu_layout->addLayout(v_layout);
}

void MenuView::action_exit() {
    QMessageBox::StandardButton answer = QMessageBox::question(nullptr, "Mensaje", "Desea salir?");
    if (answer == QMessageBox::Yes) {
        close();
    }
}
void MenuView::action_play() {
    lobby.update_join_list();
    stack.setCurrentIndex(1);
}

void MenuView::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPixmap bg("assets/gfx/screens/"
               "tittleGame.jpg");
    painter.drawPixmap(this->rect(), bg);
    QWidget::paintEvent(event);
}

/*
Para recordar:
- AddWidget añade una pagina al stack, es decir, la añade a la cola de paginas

- GoTo busca en el stack la pagina que se solicita acceder y si esta la mete en
el historial sirve para poder hacer bien lo del back

- Back simplemente retrocede una posicion del historial, fijate que si decis
GoTo y desp back, te devuelve al anterior
*/
void MenuView::add_widget(QWidget* page) { stack.addWidget(page); }

void MenuView::go_to(QWidget* destine) {
    if (stack.indexOf(destine) != -1) {
        history.push_back(stack.currentWidget());
        stack.setCurrentWidget(destine);
    }
}

void MenuView::back() {
    if (!history.empty()) {
        QWidget* previous = history.back();
        history.pop_back();
        stack.setCurrentWidget(previous);
    } else {
        stack.setCurrentIndex(0);
    }
}

MenuView::~MenuView() {}
