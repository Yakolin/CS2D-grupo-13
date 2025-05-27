#include "lobbyView.h"

LobbyView::LobbyView(ClientProtocol& protoccol):
        protocol(protoccol),
        tabs(new QTabWidget(this)),
        infoPlayer(),
        options_map(),
        img_maps()
{            
    tabs->setWindowTitle("Create Game");
    tabs->setStyleSheet("background-color:rgb(213, 207, 207);");
    tabs->resize(500, 500);
    tabs->setTabShape(QTabWidget::Rounded);
    tabs->setTabsClosable(false);
    tabs->setMovable(true);

    options_map << "Desierto"<< "Pueblito Azteca"<< "Zona de Entrenamiento";
    img_maps["Desierto"] = "assets/gfx/tiles/default_inferno.png";
    img_maps["Pueblito Azteca"] = "assets/gfx/tiles/default_aztec.png";
    img_maps["Zona de Entrenamiento"] = "assets/gfx/tiles/default_dust.png";
}


QListWidget* LobbyView::create_item(QWidget* parent, const QStringList& options) {

    QListWidget* list_map = new QListWidget(parent);
    list_map->setStyleSheet("QListWidget::item { margin-bottom: 5px; }");

    QFont fuente;
    list_map->setFont(fuente); 

    for (const QString& text: options) {
        list_map->addItem(text);
    }
    return list_map;
}

void LobbyView::section_maps(QWidget* tabMap , const std::map<QString, QString>& options,const QStringList& items_text) {

    QLabel* labelMap = new QLabel();

    QListWidget* list_map = create_item(tabMap, items_text);
    QVBoxLayout* layoutMap = new QVBoxLayout(tabMap);  // tabs
    layoutMap->addWidget(list_map);
    layoutMap->addWidget(labelMap);

    connect(list_map, &QListWidget::itemClicked,
            [this, labelMap,  options](QListWidgetItem* item) {
                QString nombre = item->text();
                infoPlayer.map = nombre.toStdString();
                labelMap->setPixmap(QPixmap(options.at(nombre)));
            });
}

void LobbyView::section_dates(QWidget* selection){
    
    QLineEdit* name = new QLineEdit(selection);
    QLineEdit* name_game = new QLineEdit(selection);

    QFormLayout *formLayout = new QFormLayout(selection);
    formLayout->addRow("Name Player: ", name);
    formLayout->addRow("Name Game: ", name_game);
    
    connect(name, &QLineEdit::textChanged, this, [&](const QString &text){
        this->infoPlayer.info.name_player = text.toStdString();
    });
    connect(name_game, &QLineEdit::textChanged, this, [&](const QString &text){
        this->infoPlayer.info.name_game = text.toStdString();
    });
    
}

void LobbyView::section_player(QWidget* selection, QPushButton* boton){

    QFormLayout* layout = new QFormLayout(selection);
    QComboBox* unidadCombo = new QComboBox(selection);
    unidadCombo->addItems({"Counter Terrorist", "Terrorist"});

    QComboBox* skinCombo = new QComboBox(selection);
    
    layout->addRow("Unidad:", unidadCombo);
    layout->addRow("Skin:", skinCombo);
    layout->addRow(boton);

    QMap<QString, QStringList> skinsPorUnidad;
    skinsPorUnidad["Counter Terrorist"] = QStringList{"Seal Force", "German GSG-9", "UK SAS", "French GIGN"};
    skinsPorUnidad["Terrorist"] = QStringList{"Phoenix", "L337 Krew", "Arctic Avenger", "Guerrilla"};


    connect(unidadCombo, &QComboBox::currentTextChanged, [this, skinCombo, skinsPorUnidad](const QString& unidad) {
        skinCombo->clear();
        skinCombo->addItems(skinsPorUnidad[unidad]);
        infoPlayer.team = unidad.toStdString();

    });
    connect(skinCombo, &QComboBox::currentTextChanged, [this, skinCombo](const QString& skin) {
        infoPlayer.skin = skin.toStdString();
    });
}

void imprimirPlayer(const Player& p) {
    std::cout << "Nombre del jugador: " << p.info.name_player << std::endl;
    std::cout << "Nombre del juego: " << p.info.name_game << std::endl;
    std::cout << "Equipo: " << p.team << std::endl;
    std::cout << "Skin: " << p.skin << std::endl;
    std::cout << "Mapa: " << p.map << std::endl;
}


void LobbyView::action_create() {
    
    QWidget* tabMap = new QWidget();

    QWidget* tabDatos = new QWidget();
    QWidget* tabPlayers = new QWidget();

    tabs->addTab(tabDatos, "Datos");
    tabs->addTab(tabMap, "Maps");
    tabs->addTab(tabPlayers, "personaje");

    QPushButton* boton = new QPushButton("Aceptar");

    section_maps(tabMap, img_maps, options_map);
    section_dates(tabDatos);
    section_player(tabPlayers,boton);

    connect(boton,  &QPushButton::clicked, [this, boton]() {
        close();
        QApplication::quit();
        imprimirPlayer(infoPlayer);
        protocol.send_create_game(infoPlayer.info.name_game);
        std::cout  << "envio nombre craet partida\n";

    });
}

void LobbyView::action_list(const std::vector<std::string>& list) {
    
    QStringList options;
    for (const std::string& name_game : list) {
        options << QString::fromStdString(name_game);
    }
    QWidget* window = new QWidget();
    tabs->addTab(window, "partidas");

    create_item(window, options);
}

void LobbyView::action_join(const std::vector<std::string> list){

    QWidget* window = new QWidget();
    QWidget* window_players = new QWidget();
    QStringList options;
    QVBoxLayout* layout = new QVBoxLayout(window);

    QPushButton* button = new QPushButton("Aceptar");

    QWidget* formWidget = new QWidget(window);

    QFormLayout *formLayout = new QFormLayout();
    
    formWidget->setLayout(formLayout);

    QLineEdit* name = new QLineEdit(window);
    formLayout->addRow("Name Player: ", name);

    for (const std::string& name_game : list) {
        options << QString::fromStdString(name_game);
    }
    tabs->addTab(window, "partidas");
    tabs->addTab(window_players, "Players");
    section_player(window_players,button);

    QListWidget* list_games = create_item(window, options);

    connect(list_games, &QListWidget::itemClicked,[this,  options](QListWidgetItem* item) {
        qDebug() << item->text();
    });
    
    layout->addWidget(list_games);
    layout->addWidget(formWidget); 
    layout->addWidget(button);
    connect(button,  &QPushButton::clicked, [this, button]() {
        close();
        QApplication::quit();
        std::cout  << "envio nombre join partida: "<< infoPlayer.info.name_game << std::endl;
        protocol.send_join_game(infoPlayer.info.name_game);
    });

}
void LobbyView::action_join2(){

    QWidget* window = new QWidget();
    QWidget* window_players = new QWidget();

    QVBoxLayout* layout = new QVBoxLayout(window);

    QPushButton* button = new QPushButton("Aceptar");

    QWidget* formWidget = new QWidget(window);

    QFormLayout *formLayout = new QFormLayout();
    
    formWidget->setLayout(formLayout);

    QLineEdit* name = new QLineEdit(window);
    QLineEdit* name_game = new QLineEdit(window);
    formLayout->addRow("Name Player: ", name);
    formLayout->addRow("Name Game: ", name_game);

    tabs->addTab(window, "partida");
    tabs->addTab(window_players, "Players");
    section_player(window_players,button);

    connect(name_game ,&QLineEdit::textChanged, this, [&](const QString &text){
        this->infoPlayer.info.name_game = text.toStdString();
        std::cout  << "nombre partida: "<< infoPlayer.info.name_game << std::endl;
    });
    connect(name,&QLineEdit::textChanged, this, [&](const QString &text){
        this->infoPlayer.info.name_player = text.toStdString();
    });
    layout->addWidget(formWidget); 
    layout->addWidget(button);
    connect(button,  &QPushButton::clicked, [this, button]() {
        close();
        QApplication::quit();
        std::cout  << "envio nombre join partida: "<< infoPlayer.info.name_game << std::endl;
        protocol.send_join_game(infoPlayer.info.name_game);
    });
    

}
LobbyView::~LobbyView() {}


/*  
    QObject::connect(botonAceptar, &QPushButton::clicked, [=]() mutable{
        info.name_player = name->text().toStdString();
        info.name_game = name_game->text().toStdString();

        qDebug() << "Jugador:" << QString::fromStdString(info.name_player);
        qDebug() << "Juego:" << QString::fromStdString(info.name_game);
    });
    
    //  (Seal force, German GSG-9, UK SAS o French GIGN
    img_skins_counter_terrorist["Seal Force"] = "assets/gfx/player/ct3.bmp";
    img_skins_counter_terrorist["German GSG-9"] = "assets/gfx/player/ct1.bmp";
    img_skins_counter_terrorist["UK SAS"] = "assets/gfx/player/ct4.bmp";
    img_skins_counter_terrorist["French GIGN"] = "assets/gfx/player/ct2_bmp";

    // Skins Terrorist
    img_skins_terrorist["Phoenix"] = "assets/gfx/player/t4.bmp";  //
    img_skins_terrorist["L337 Krew"] = "assets/gfx/player/t1.bmp";
    img_skins_terrorist["Arctic Avenger"] = "assets/gfx/player/t3.bmp";  //
    img_skins_terrorist["Guerrilla"] = "assets/gfx/player/t2.bmp";       //*/