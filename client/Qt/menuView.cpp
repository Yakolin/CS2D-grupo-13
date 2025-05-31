#include "menuView.h"
const int HEIGHT_MENU = 500;
const int WIDTH_MENU = 500;

#define OPCION_CREATE "Create Game"
#define OPCION_JOIN "Join Game"
#define OPCION_EXIT "Exit Game"
#define OPCION_LIST "List Game"
#define OPCION_HELP "Help Game"
#define OPCION_MENU "Volver a Menu"

MenuView::MenuView(QWidget* parent, ClientProtocol& protocol):
        QWidget(parent),
        stack(this),
        menu(),
        lobby(protocol),
        protocolo(protocol) 
        {
    stack.setFixedSize(500, 500);  

    QLabel* img_icono = new QLabel(this);
    QPixmap img_img("assets/gfx/cs2d.png");
    img_icono->setPixmap(img_img);

    menu.setWindowTitle("Counter Strike");
    resize(WIDTH_MENU, HEIGHT_MENU);


    QWidget *page_create = new QWidget();
    QWidget *page_help = new QWidget();
    QTabWidget *page_join = new QTabWidget();

    QPushButton* button_menu = new QPushButton(OPCION_MENU);
    QPushButton* button_menu2 = new QPushButton(OPCION_MENU);
    QPushButton* button_menu3 = new QPushButton(OPCION_MENU);

    lobby.action_create(page_create, button_menu);
    lobby.action_join(page_join, button_menu2);
    lobby.action_help(page_help ,button_menu3);

    stack.addWidget(&menu);         
    stack.addWidget(page_create);  
    stack.addWidget(page_join);    
    stack.addWidget(page_help);    

    QVBoxLayout* layout = new QVBoxLayout(&menu); 
    layout->addWidget(img_icono, 0, Qt::AlignCenter);


    add_button(layout, OPCION_CREATE,[this]() { this->action_create();});
    add_button(layout, OPCION_JOIN,[this]() { this->action_join(); });
    add_button(layout, OPCION_HELP,[this]() { this->action_help(); });

    QObject::connect(button_menu, &QPushButton::clicked, this, &MenuView::action_menu);
    QObject::connect(button_menu2, &QPushButton::clicked, this, &MenuView::action_menu);
    QObject::connect(button_menu3, &QPushButton::clicked, this, &MenuView::action_menu);
    connect(&lobby, &LobbyView::opcionElegida, this, &MenuView::opcionElegida);

}


void MenuView::action_exit() {
    QMessageBox::StandardButton answer = QMessageBox::question(nullptr, "Mensaje", "Desea salir?");
    if (answer == QMessageBox::Yes) {
        close();
    }
}
void MenuView::action_create() {
    stack.setCurrentIndex(1);
}
void MenuView::action_join() {

    protocolo.send_list_games();
    std::vector<std::string> list = protocolo.read_list_games();
    lobby.update_join_list(list); 
    stack.setCurrentIndex(2);
}

void MenuView::action_menu() {  stack.setCurrentIndex(0);}

void MenuView::action_help() {stack.setCurrentIndex(3);}

void MenuView::add_button(QVBoxLayout* layout, const QString& text, std::function<void()> callback){
    QPushButton* button = new QPushButton(text);
    button->setFixedSize(200, 50);
    QObject::connect(button, &QPushButton::clicked, [callback,this]() { callback();});
    layout->addWidget(button, 0, Qt::AlignHCenter);
}



MenuView::~MenuView() {}

