#ifndef VISTA_H
#define VISTA_H
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

class Vista : public QWidget {
    Q_OBJECT  // ¡Obligatorio para señales y slots!

public slots:
    void on_item_clicked(QTreeWidgetItem *item, int column);

private:

    /*
    pre:-
    post: crea una celda para la tabla de puntajes
    */
    QLabel* cell(const QString &text, const bool& bold);
    /*
    pre: recibe un mapa cargado con los puntajes de los jugadores y un QVBoxLayout 
    post: crea una tabla con los puntajes de los jugadores y lo apila en el QVBoxLayout
    */
    void add_table(QVBoxLayout *scores_table, const std::map<std::string, PlayerSummary>& scores);
    /*
    pre: recibe un QVBoxLayout y un ranking de los equipos cargados.
    post: apila los rankings de los equipos en el QVBoxLayout.
    */
    void add_ranking(QVBoxLayout *scores_table, Rankings& ranking);

    void add_button(QVBoxLayout *layout, const QString &text, const std::function<void()> &action);

    void action_create() ;
    void action_join() ;
    void action_exit() ;
    void action_help() ;

    void add_sub_options( QTreeWidgetItem *parent , const QString &text);

    void create_item(QTreeWidget *parent , const QStringList &options, const QString &text );



    void config_windows(QWidget *ventana, const QString &text, int width, int height);

public:
    /*
    pre: recibe los argumentos de la aplicacion
    post: inicia la aplicacion
    */
    int run(int& argc, char *argv[]);

    /*
    pre:-
    post: muestra el menu de opciones al empezar el juego
    */
    int menu();
    /*
    pre: recibe un mapa cargado con los puntajes de los jugadores y un ranking de los equipos
    post: muestra los puntajes del juego
    */
    int scores_game(const std::map<std::string, PlayerSummary>& scores,  Rankings& ranking);

};

#endif // VISTA_H