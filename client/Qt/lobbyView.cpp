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

    QComboBox* combo_terrorist = new QComboBox(selection);
    QComboBox* combo_counter_terrorist = new QComboBox(selection);

    QStringList list_terrorist = {"Seal Force", "German GSG-9", "UK SAS", "French GIGN"};
    QStringList list_counter = {"Phoenix", "L337 Krew", "Arctic Avenger", "Guerrilla"};

    combo_terrorist->addItems(list_terrorist);
    combo_counter_terrorist->addItems(list_counter);
    layout->addRow("Counter Terrorist:", combo_terrorist);
    layout->addRow("Terrorist :", combo_counter_terrorist);

    connect(combo_terrorist, &QComboBox::currentTextChanged,
            [this, combo_terrorist](const QString& skin) { infoPlayer.skin = skin.toStdString(); });

    connect(combo_counter_terrorist, &QComboBox::currentTextChanged,
            [this, combo_counter_terrorist](const QString& skin) {
                infoPlayer.skin2 = skin.toStdString();
            });
}

void imprimirPlayer(const Player& p) {
    std::cout << "Nombre del jugador: " << p.info.name_player << std::endl;
    std::cout << "Nombre del juego: " << p.info.name_game << std::endl;
    std::cout << "Equipo: " << p.team << std::endl;
    std::cout << "Skin: " << p.skin << std::endl;
    std::cout << "Mapa: " << p.map << std::endl;
}

MapName LobbyView::get_map(const std::string map) {
    if (map == "Desierto")
        return MapName::DESIERTO;
    if (map == "Pueblito Azteca")
        return MapName::PUEBLITO_AZTECA;
    return MapName::ZONA_ENTRENAMIENTO;
}

CounterTerroristSkin LobbyView::get_skin_counter(const std::string skin_counter) {
    if (skin_counter == "Seal Force")
        return CounterTerroristSkin::SEAL;
    if (skin_counter == "German GSG-9")
        return CounterTerroristSkin::GSG9;
    if (skin_counter == "UK SAS")
        return CounterTerroristSkin::SAS;
    return CounterTerroristSkin::GIGN;
}

TerroristSkin LobbyView::get_skin_terrorist(const std::string skin_terrorist) {
    if (skin_terrorist == "Phoenix")
        return TerroristSkin::PHOENIX;
    if (skin_terrorist == "L337 Krew")
        return TerroristSkin::L337_KREW;
    if (skin_terrorist == "Arctic Avenger")
        return TerroristSkin::ARCTIC_AVENGER;
    return TerroristSkin::GUERRILLA;
}

void LobbyView::function_join() {

    Skins skins(get_skin_counter(infoPlayer.skin2), get_skin_terrorist(infoPlayer.skin));
    protocol.send_join_game(JoinGame(infoPlayer.info.name_game, skins));
    emit opcionElegida(LobbyCommandType::JOIN_GAME, infoPlayer);
}

void LobbyView::function_create() {
    std::cout << "envio nombre create partida: " << infoPlayer.info.name_game << std::endl;
    MapName map_name(get_map(infoPlayer.map));
    Skins skins(get_skin_counter(infoPlayer.skin2), get_skin_terrorist(infoPlayer.skin));


    protocol.send_create_game(CreateGame(infoPlayer.info.name_game, map_name, skins));
    emit opcionElegida(LobbyCommandType::CREATE_GAME, infoPlayer);
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
        QString qpartida = QString::fromStdString(partida);
        list_games->addItem(QString::fromStdString(partida));
        qDebug() << "Partida añadida:" << QString::fromStdString(partida);
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
