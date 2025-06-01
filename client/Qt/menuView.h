#ifndef MENU_VIEW_H
#define MENU_VIEW_H
#include <QDebug>
#include <QFont>
#include <QFormLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QListWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QPixmap>
#include <QPushButton>
#include <QStackedWidget>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QWidget>
#include <functional>
#include <iostream>
#include <map>

#include "../../common/lobby_types.h"
#include "../model/protocol.h"
#include "../tipos.h"

#include "lobbyView.h"


class MenuView: public QWidget {
    Q_OBJECT

signals:
    void opcionElegida(LobbyCommandType tipo);


public slots:
    void manejar_opcion(LobbyCommandType opcion) { emit opcionElegida(opcion); }

private:
    QStackedWidget stack;
    QWidget menu;
    LobbyView lobby;
    ClientProtocol& protocolo;


    /*
    pre:
    post:
    */
    void add_button(QVBoxLayout* layout, const QString& text, std::function<void()> callback);

public:
    MenuView(QWidget* parent, ClientProtocol& protocol);
    /*
    pre:-
    post: muestra el menu de opciones al empezar el juego
    */
    void run();

    LobbyCommandType getCommantType() const;
    void action_menu();
    void action_create();
    void action_join();
    void action_help();
    void action_exit();
    ~MenuView();
};

#endif  // MENU_VIEW_H
