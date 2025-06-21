#ifndef MENU_VIEW_H
#define MENU_VIEW_H
#include <map>

#include "../../common/lobby_types.h"
#include "../model/protocol.h"
#include "../tipos.h"

#include "ButtonsCreator.h"
#include "StackNavigator.h"
#include "lobbyView.h"


#define PAGE_PLAY_STYLE \
    R"( QTabWidget::pane { border: 2px solid #444;border-radius: 6px;background-color:rgba(116, 116, 115, 0.27);padding: 10px;})"
class MenuView: public QWidget, public StackNavigator {
    Q_OBJECT

signals:
    void opcionElegida(LobbyCommandType tipo, Player infoPlayer);

public slots:
    void manejar_opcion(LobbyCommandType opcion, Player infoPlayer) {
        emit opcionElegida(opcion, infoPlayer);
    }

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::vector<QWidget*> history;
    QStackedWidget stack;
    QMediaPlayer* music;
    QMediaPlaylist* playlist;
    QWidget menu;
    LobbyView lobby;
    ButtonsCreator buttons_creator;
    ClientProtocol& protocol;
    /*
    pre:
    post:
    */
    void add_buttons_menu(QVBoxLayout* layout);
    void start_music();

public:
    MenuView(QWidget* parent, ClientProtocol& protocol);
    /*
    pre:-
    post: muestra el menu de opciones al empezar el juego
    */
    void run();

    LobbyCommandType getCommantType() const;
    void action_play();
    void action_exit();
    virtual void add_widget(QWidget* page) override;
    virtual void go_to(QWidget* destine) override;
    virtual void back() override;
    virtual ~MenuView();
};

#endif  // MENU_VIEW_H
