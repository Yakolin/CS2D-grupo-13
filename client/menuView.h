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
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QWidget>
#include <functional>
#include <map>

#include "lobbyView.h"
#include "tipos.h"


class MenuView {

private:
    QMainWindow* window;
    QLabel* img_icono;
    InfoGame info_game;
    QString clicked_text;
    std::map<QString, GameMenu> botones;

public:
    MenuView();
    /*
    pre:-
    post: muestra el menu de opciones al empezar el juego
    */
    GameMenu run();
    /*
    pre: recibe un QVBoxLayout y un ranking de los equipos cargados.
    post: apila los rankings de los equipos en el QVBoxLayout.
    */
    void add_button(QVBoxLayout* layout, const QString& text);
    void action_create();
    void action_join();
    void action_help();
    void action_exit();

    ~MenuView();
};

#endif  // MENU_VIEW_H
