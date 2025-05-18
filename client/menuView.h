#ifndef MENU_VIEW_H
#define MENU_VIEW_H
#include "lobbyView.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "tipos.h"
#include <QObject>
#include <QPixmap>
#include <QString>
#include <functional>
#include <QDebug>
#include <map>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QTableWidgetItem>
#include <QWidget>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QIcon>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFont>
#include <functional>
#include <QListView>
#include <QListWidget>


class MenuView {

private:
    QMainWindow *window;
    QLabel *img_icono;
    InfoGame info_game;
    QString clicked_text;
    std::map<QString,GameMenu> botones;

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
        void add_button(QVBoxLayout *layout, const QString &text);
        void action_create();
        void action_join();
        void action_help();
        void action_exit();

        ~MenuView();
    };

    #endif // MENU_VIEW_H