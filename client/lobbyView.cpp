#include "lobbyView.h"
#include <QDebug>
#include <QTabWidget>
#include <QListWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QStringList>
#include <QPixmap>
#include <map>
LobbyView::LobbyView() :
    tabs(new QTabWidget(this)),
    options_map(),
    options_skins(),
    options_unidad(),
    img_maps(),
    img_skins_terrorist(),
    img_skins_counter_terrorist()
{
    tabs->setWindowTitle("Create Game");
    tabs->setStyleSheet("background-color:rgb(198, 199, 199);");
    tabs->resize(500, 500);
    tabs->setTabShape(QTabWidget::Rounded);
    tabs->setTabsClosable(false);
    tabs->setMovable(true);

    options_map << "Desierto" << "Pueblito Azteca" << "Zona de Entrenamiento";
    options_skins << "Phoenix" << "L337 Krew" << "Arctic Avenger" << "Guerrilla";
    options_unidad << "Counter terrorists" << "Terrorist" ;

    img_maps["Desierto"] = "../assets/gfx/tiles/default_inferno.png";
    img_maps["Pueblito Azteca"] = "../assets/gfx/tiles/default_aztec.png";
    img_maps["Zona de Entrenamiento"] = "../assets/gfx/tiles/default_dust.png";
    //  (Seal force, German GSG-9, UK SAS o French GIGN
    img_skins_counter_terrorist["Seal Force"] = "../assets/gfx/player/ct3.bmp";
    img_skins_counter_terrorist["German GSG-9"] = "../assets/gfx/player/ct1.bmp";
    img_skins_counter_terrorist["UK SAS"] = "../assets/gfx/player/ct4.bmp";
    img_skins_counter_terrorist["French GIGN"] = "../assets/gfx/player/ct2_bmp";

    // Skins Terrorist
    img_skins_terrorist["Phoenix"] = "../assets/gfx/player/t4.bmp"; //
    img_skins_terrorist["L337 Krew"] = "../assets/gfx/player/t1.bmp";
    img_skins_terrorist["Arctic Avenger"] = "../assets/gfx/player/t3.bmp"; //
    img_skins_terrorist["Guerrilla"] = "../assets/gfx/player/t2.bmp"; //
}


QListWidget * LobbyView::create_item( QWidget *parent , const QStringList &options, const QString &text) {

    qDebug() << text;
    QListWidget *list_map = new QListWidget(parent);
    QFont fuente;
    // fuente.setPointSize(10); // tamaño letra
    //fuente.setBold(true); // negrita
    list_map->setFont(fuente); // fuente

    for (const QString &text : options) {
        list_map->addItem(text);
    }
    return list_map;
}

void LobbyView::section_maps(const QString &text, const std::map<QString,QString>& options, const QStringList &items_text){

    QLabel *labelMap = new QLabel();
    QWidget *tabMap = new QWidget();
    tabs->addTab(tabMap, text);
    QListWidget *list_map = create_item(tabMap, items_text, text);
    QHBoxLayout *layoutMap = new QHBoxLayout(tabMap); // tabs
    layoutMap->addWidget(list_map);
    layoutMap->addWidget(labelMap);
    QListWidgetItem* selected = nullptr;

    connect(list_map, &QListWidget::itemClicked, [this,labelMap, &selected, options](QListWidgetItem *item){
        QString nombre = item->text();
        selected = item;
        labelMap->setPixmap(QPixmap(options.at(nombre)));
    });
}

void LobbyView::action_create() {

    section_maps("Maps", img_maps ,options_map );
    QLabel *labelOptions = new QLabel();
    QLabel *labelPlayers = new QLabel();

    QWidget *tabOptions = new QWidget();
    QWidget *tabPlayers = new QWidget();

    tabs->addTab(tabOptions, "Skins");
    tabs->addTab(tabPlayers, "Players");

    QListWidget *list_options = create_item(tabOptions,  options_skins, "Skins");
    QListWidget *list_unidad = create_item(tabPlayers, options_unidad, "Unidades");


    QHBoxLayout *layoutOptions = new QHBoxLayout(tabOptions); // tabs
    layoutOptions->addWidget(list_options);
    layoutOptions->addWidget(labelOptions);

    QHBoxLayout *layoutPlayers = new QHBoxLayout(tabPlayers); // tabs
    layoutPlayers->addWidget(list_unidad);
    layoutPlayers->addWidget(labelPlayers);
  //  QListWidgetItem* selected = nullptr;


}

LobbyView::~LobbyView(){}