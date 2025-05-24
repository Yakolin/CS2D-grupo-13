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
#include <iostream>
#include <map>
#include "../../common/lobby_types.h"
#include "lobbyView.h"
#include "../tipos.h"


class MenuView : public QDialog{
    Q_OBJECT

signals:
    void opcionElegida(LobbyCommandType opcion);
private:
    QLabel* img_icono;
    QString clicked_text;
    std::map<QString,LobbyCommandType > botones;

    /*
    pre: recibe un QVBoxLayout y un ranking de los equipos cargados.
    post: apila los rankings de los equipos en el QVBoxLayout.
    */
    void add_button(QVBoxLayout* layout, const QString& text);

public:
    MenuView(QWidget* parent = nullptr);
    /*
    pre:-
    post: muestra el menu de opciones al empezar el juego
    */
    void run();

    LobbyCommandType getCommantType() const;
    
    void action_create();
    void action_join(std::vector<std::string>& list );
    void action_help();
    void action_exit();
    void action_list(const std::vector<std::string>& list);
    ~MenuView();
};

#endif  // MENU_VIEW_H
