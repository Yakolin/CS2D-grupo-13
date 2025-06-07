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
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "../../common/lobby_action.h"
#include "../../common/lobby_types.h"
#include "../model/protocol.h"
#include "../tipos.h"

class LobbyView: public QWidget {
    Q_OBJECT
signals:
    void opcionElegida(LobbyCommandType opcion);

public:
    LobbyView(ClientProtocol& protoccol);

    void action_create(QWidget* page_create, QPushButton* button_menu);

    void action_join(QTabWidget* page_join, QPushButton* button_menu);

    void action_help(QWidget* page_help, QPushButton* button_menu);

    QListWidget* create_item(QWidget* parent, const QStringList& options);

    void update_join_list(const std::vector<std::string>& nuevas_partidas);

    virtual ~LobbyView();


private:
    ClientProtocol& protocol;
    Player infoPlayer;
    QStringList options_map;
    std::map<QString, QString> img_maps;
    QListWidget* list_games;

    void section_maps(QWidget* tabMap, const std::map<QString, QString>& options,
                      const QStringList& items_text);
    void function_join();
    void function_create();
    void section_dates(QWidget* section);
    void section_player(QWidget* selection);
    void action_button(QVBoxLayout* layout, const QString& text, std::function<void()> callback);
};

#endif  // LOBBY_VIEW_H
