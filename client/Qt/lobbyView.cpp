#include "lobbyView.h"
#define BUTTON_CREATE "Create"
#define BUTTON_JOIN "Join"

LobbyView::LobbyView(ClientProtocol& protoccol):
        protocol(protoccol),
        infoPlayer(),
        options_map(),
        img_maps(),
        list_games(new QListWidget(this)) {

    options_map << "Desierto"
                << "Pueblito Azteca"
                << "Zona de Entrenamiento";
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

void LobbyView::section_maps(QWidget* tabMap, const std::map<QString, QString>& options,
                             const QStringList& items_text) {

    QLabel* labelMap = new QLabel();

    QListWidget* list_map = create_item(tabMap, items_text);
    QVBoxLayout* layoutMap = new QVBoxLayout(tabMap);  // tabs
    layoutMap->addWidget(list_map);
    layoutMap->addWidget(labelMap);

    connect(list_map, &QListWidget::itemClicked, [this, labelMap, options](QListWidgetItem* item) {
        QString nombre = item->text();
        infoPlayer.map = nombre.toStdString();
        labelMap->setPixmap(QPixmap(options.at(nombre)).scaled(300, 300, Qt::KeepAspectRatio));
    });
}

void LobbyView::section_dates(QWidget* selection) {

    QLineEdit* name = new QLineEdit(selection);
    QLineEdit* name_game = new QLineEdit(selection);

    QFormLayout* formLayout = new QFormLayout(selection);
    formLayout->addRow("Name Player: ", name);
    formLayout->addRow("Name Game: ", name_game);

    connect(name, &QLineEdit::textChanged, this,
            [&](const QString& text) { this->infoPlayer.info.name_player = text.toStdString(); });
    connect(name_game, &QLineEdit::textChanged, this,
            [&](const QString& text) { this->infoPlayer.info.name_game = text.toStdString(); });
}

void LobbyView::section_player(QWidget* selection) {

    QFormLayout* layout = new QFormLayout(selection);
    QComboBox* unidadCombo = new QComboBox(selection);
    unidadCombo->addItems({"Counter Terrorist", "Terrorist"});

    QComboBox* skinCombo = new QComboBox(selection);

    layout->addRow("Unidad:", unidadCombo);
    layout->addRow("Skin:", skinCombo);


    QMap<QString, QStringList> skinsPorUnidad;
    skinsPorUnidad["Counter Terrorist"] =
            QStringList{"Seal Force", "German GSG-9", "UK SAS", "French GIGN"};
    skinsPorUnidad["Terrorist"] =
            QStringList{"Phoenix", "L337 Krew", "Arctic Avenger", "Guerrilla"};


    connect(unidadCombo, &QComboBox::currentTextChanged,
            [this, skinCombo, skinsPorUnidad](const QString& unidad) {
                skinCombo->clear();
                skinCombo->addItems(skinsPorUnidad[unidad]);
                infoPlayer.team = unidad.toStdString();
            });
    connect(skinCombo, &QComboBox::currentTextChanged,
            [this, skinCombo](const QString& skin) { infoPlayer.skin = skin.toStdString(); });
}

void imprimirPlayer(const Player& p) {
    std::cout << "Nombre del jugador: " << p.info.name_player << std::endl;
    std::cout << "Nombre del juego: " << p.info.name_game << std::endl;
    std::cout << "Equipo: " << p.team << std::endl;
    std::cout << "Skin: " << p.skin << std::endl;
    std::cout << "Mapa: " << p.map << std::endl;
}

void LobbyView::function_join() {

    protocol.send_join_game(JoinGame(infoPlayer.info.name_game));
    emit opcionElegida(LobbyCommandType::JOIN_GAME);
}
void LobbyView::function_create() {

    std::cout << "envio nombre create partida: " << infoPlayer.info.name_game << std::endl;
    protocol.send_create_game(CreateGame(infoPlayer.info.name_game, "pepito"));
    emit opcionElegida(LobbyCommandType::CREATE_GAME);
}

void LobbyView::action_button(QVBoxLayout* layout, const QString& text,
                              std::function<void()> callback) {

    QPushButton* button = new QPushButton(text);
    QObject::connect(button, &QPushButton::clicked, [callback, this]() { callback(); });
    layout->addWidget(button, 0, Qt::AlignHCenter);
}
void LobbyView::action_create(QWidget* page, QPushButton* button_menu) {
    QVBoxLayout* layout = new QVBoxLayout(page);
    QTabWidget* page_create = new QTabWidget();

    QWidget* tabMap = new QWidget();
    QWidget* tabDatos = new QWidget();
    QWidget* tabPlayers = new QWidget();

    page_create->addTab(tabDatos, "Datos");
    page_create->addTab(tabMap, "Maps");
    page_create->addTab(tabPlayers, "personaje");

    layout->addWidget(page_create);

    section_maps(tabMap, img_maps, options_map);
    section_dates(tabDatos);
    section_player(tabPlayers);

    action_button(layout, BUTTON_CREATE, [this]() { this->function_create(); });
    layout->addWidget(button_menu);
}

void LobbyView::update_join_list(const std::vector<std::string>& nuevas_partidas) {
    list_games->clear();
    for (const std::string& partida: nuevas_partidas) {
        list_games->addItem(QString::fromStdString(partida));
    }
}

void LobbyView::action_join(QTabWidget* page_join, QPushButton* button_menu) {

    QWidget* window = new QWidget();
    QWidget* window_players = new QWidget();
    QStringList options;
    QVBoxLayout* layout = new QVBoxLayout(window);

    QWidget* formWidget = new QWidget(window);

    QFormLayout* formLayout = new QFormLayout();

    formWidget->setLayout(formLayout);

    QLineEdit* name = new QLineEdit(window);
    formLayout->addRow("Name Player: ", name);

    page_join->addTab(window, "partidas");
    page_join->addTab(window_players, "Players");
    section_player(window_players);

    this->list_games = create_item(window, options);

    connect(this->list_games, &QListWidget::itemClicked, [this, options](QListWidgetItem* item) {
        qDebug() << item->text();
        infoPlayer.info.name_game = item->text().toStdString();
    });

    layout->addWidget(list_games);
    layout->addWidget(formWidget);
    action_button(layout, BUTTON_JOIN, [this]() { this->function_join(); });
    layout->addWidget(button_menu);
}

void LobbyView::action_help(QWidget* page_help, QPushButton* button_menu) {

    QVBoxLayout* layout = new QVBoxLayout(page_help);

    QTextEdit* helpText = new QTextEdit(page_help);
    helpText->setReadOnly(true);


    QFont fuente("Segoe UI", 11);
    helpText->setFont(fuente);

    helpText->setHtml("<style>"
                      "body { color: #2E2E2E; font-family: 'Segoe UI'; background-color: #f5f5f5; "
                      "padding: 10px; }"
                      "h2 { color: #007acc; margin-bottom: 15px; }"
                      "p { margin: 8px 0; font-size: 13px; }"
                      "b { color: #444; }"
                      "</style>"
                      "<body>"
                      "<h2>Ayuda</h2>"
                      "<p><b>Create Game:</b> Para crear una partida nueva.</p>"
                      "<p><b>Join Game:</b> Para unirse a una partida existente.</p>"
                      "</body>");


    helpText->setStyleSheet("QTextEdit { border: none; background-color: #f5f5f5; }");

    layout->addWidget(helpText);
    layout->addWidget(button_menu);
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