#ifndef LOBBY_VIEW_H
#define LOBBY_VIEW_H
#include <QLabel>
#include <QLayout>
#include <QListWidget>
#include <QStringList>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QComboBox>
#include <QApplication>
#include <functional>
#include <QFormLayout>
#include <string>
#include <QLineEdit>
#include <iostream>
#include <map>
#include "../common/lobby_types.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QPixmap>
#include "tipos.h"
#include <QPushButton>
#include <QMessageBox>

class LobbyView: public QWidget {
    Q_OBJECT

public:
    LobbyView();

    void action_create();

    void action_join(const std::vector<std::string> list);
    
    void action_list(const std::vector<std::string>& list) ;

    QListWidget* create_item(QWidget* parent, const QStringList& options);

    virtual ~LobbyView();



private:
    QTabWidget* tabs;
    Player infoPlayer;
    QStringList options_map;
    std::map<QString, QString> img_maps;

    void section_maps(QWidget* tabMap,  const std::map<QString, QString>& options,const QStringList& items_text);

    void section_dates(QWidget* section);
    void section_player(QWidget* selection,QPushButton* boton);
};

#endif  // LOBBY_VIEW_H
