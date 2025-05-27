#ifndef LOBBY_VIEW_H
#define LOBBY_VIEW_H
#include <QApplication>
#include <QComboBox>
#include <QDebug>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>
#include <QStringList>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "../common/lobby_types.h"

#include "tipos.h"

class LobbyView: public QWidget {
    Q_OBJECT

public:
    LobbyView();

    void action_create();

    void action_join(const std::vector<std::string> list);

    void action_list(const std::vector<std::string>& list);

    QListWidget* create_item(QWidget* parent, const QStringList& options);

    virtual ~LobbyView();


private:
    QTabWidget* tabs;
    Player infoPlayer;
    QStringList options_map;
    std::map<QString, QString> img_maps;

    void section_maps(QWidget* tabMap, const std::map<QString, QString>& options,
                      const QStringList& items_text);

    void section_dates(QWidget* section);
    void section_player(QWidget* selection, QPushButton* boton);
};

#endif  // LOBBY_VIEW_H
