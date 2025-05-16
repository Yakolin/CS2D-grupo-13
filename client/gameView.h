#ifndef GAME_VIEW_H
#define GAME_VIEW_H
#include <SDL2/SDL.h>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QTableWidgetItem>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QPixmap>
#include "tipos.h"
#include <QIcon>
#include <map>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFont>
#include <QDebug>
#include <functional>
#include <QTreeWidget>
#include <QObject>
#include <QListView>
#include <QListWidget>
#include "menuView.h"

class GameView {

private:

    QApplication app;
    MenuView *menu;
    GameMenu seleccion;
    /*
    pre:-
    post: crea una celda para la tabla de puntajes
    */
    QLabel* cell(const QString &text, const bool& bold);


    void config_windows(QWidget *ventana, const QString &text, int width, int height);

public:
    explicit GameView(int& argc, char *argv[]);
    /*
    pre: recibe los argumentos de la aplicacion
    post: inicia la aplicacion
    */
    GameMenu run_menu();
    ~GameView();

};

#endif // GAME_VIEW_H