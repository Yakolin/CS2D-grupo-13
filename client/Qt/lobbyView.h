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
#include <vector>

#include "../../common/lobby_action.h"
#include "../../common/lobby_types.h"
#include "../model/protocol.h"
#include "../tipos.h"

#include "ButtonsCreator.h"
#include "StackNavigator.h"


#define HELP "Tutorial"
#define PAGE_PLAYER_STYLE                                    \
    "QWidget { border: 2px solid #444; border-radius: 6px; " \
    "background-color: rgba(116, 116, 115, 0.27); padding: 10px; }"

class LobbyView: public QWidget {
    Q_OBJECT
signals:
    void opcionElegida(LobbyCommandType opcion, Player infoPlayer);

public:
    LobbyView(StackNavigator& stack_navigator, ClientProtocol& protocol);

    void play_game(QTabWidget* page_play);

    QListWidget* create_item(QWidget* parent, const QStringList& options);

    void update_join_list();

    virtual ~LobbyView();

private:
    enum class LobbyMode { JOIN, CREATE };
    ClientProtocol& protocol;
    LobbyMode modo_lobby_actual;
    StackNavigator& stack_navigator;
    Player infoPlayer;
    QStringList options_map;
    std::map<QString, QString> img_maps;
    QStringList options_skins_tt;
    std::map<QString, QString> img_skins_tt;
    QStringList options_skins_ct;
    std::map<QString, QString> img_skins_ct;
    QListWidget* list_games;
    ButtonsCreator buttons_creator;

    void set_skins_ct();
    void set_skins_tt();
    void add_help_page(QWidget* page_help);
    void add_player_page(QWidget* page_player);
    QWidget* page_player_select;
    QWidget* page_help;
    void action_help(QWidget* page_help);
    void configure_window_join(QWidget* window_join);
    void configure_window_create(QWidget* window_create);
    void section_maps(QWidget* tabMap, const std::map<QString, QString>& options,
                      const QStringList& items_text);
    void function_join();
    void function_create();
    void section_skins(QVBoxLayout* selection);
    MapName get_map(const std::string map);
    CounterTerroristSkin get_skin_counter(const std::string skin_counter);
    TerroristSkin get_skin_terrorist(const std::string skin_terrorist);
};

#endif  // LOBBY_VIEW_H
