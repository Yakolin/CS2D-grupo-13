#ifndef LOBBY_VIEW_H
#define LOBBY_VIEW_H
#include "tipos.h"

#include <QWidget>
#include <QLayout>
#include <QListWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <map>
#include <functional>
#include <QLabel>

class LobbyView : public QWidget
{
    Q_OBJECT

public:
    explicit LobbyView();
    
    void action_create();
    QListWidget *create_item(QWidget *parent, const QStringList &options, const QString &text);
    void add_button(QVBoxLayout *layout, const QString &text, const std::function<void()> &action);
    void add_tab(QTabWidget *tabs, const QString &text, QWidget *widget);

    virtual ~LobbyView();

private:
    QTabWidget *tabs;
    QStringList options_map ;
    QStringList options_skins ;
    QStringList options_unidad ;
    std::map<QString,QString> img_maps;
    std::map<QString,QString> img_skins_terrorist;
    std::map<QString,QString> img_skins_counter_terrorist;
    // Private members and methods

    void section_maps(const QString &text, const std::map<QString,QString>& options, const QStringList &items_text);
};

#endif // LOBBY_VIEW_H