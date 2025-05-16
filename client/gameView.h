#ifndef GAME_VIEW_H
#define GAME_VIEW_H
#include "tipos.h"
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

    void dibujar() ;

    bool cargarTexturaFondo(SDL_Renderer* renderer);

public:
    explicit GameView(int& argc, char *argv[]);
    /*
    pre: -
    post: muestra el menu
    */
    GameMenu run_menu();

    void start_game();


    ~GameView();

};

#endif // GAME_VIEW_H