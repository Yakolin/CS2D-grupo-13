#include "lobbyView.h"
#define BUTTON_CREATE "Create"
#define BUTTON_JOIN "Join"

LobbyView::LobbyView(StackNavigator& stack_navigator, ClientProtocol& protocol):
        protocol(protocol),
        stack_navigator(stack_navigator),
        infoPlayer(),
        options_map(),
        img_maps(),
        list_games(new QListWidget(this)) {

    options_map << "Desierto" << "Pueblito Azteca" << "Zona de Entrenamiento";
    img_maps["Desierto"] = "assets/"
                           "gfx/screens/dust2.jpg";
    img_maps["Pueblito Azteca"] = ""
                                  "assets/gfx/screens/aztecc.jpg";
    img_maps["Zona de Entrenamiento"] = "assets/gfx/screens/"
                                        "entrenamiento.jpg";
    set_skins_ct();
    set_skins_tt();
}

// Falta agregar las skins
void LobbyView::set_skins_ct() {
    this->options_skins_ct << "Phoenix" << "L337 Krew" << "Arctic Avenger" << "Guerrilla";
    this->img_skins_ct["Phoenix"] = "assets/gfx/npc/poe.png";
    this->img_skins_ct["L337 Krew"] = "assets/gfx/npc/kreew.png";
    this->img_skins_ct["Arctic Avenger"] = "assets/gfx/npc/artic.png";
    this->img_skins_ct["Guerrilla"] = "assets/gfx/npc/guerrilla.png";
}

void LobbyView::set_skins_tt() {
    this->options_skins_tt << "Seal Force" << "German GSG-9" << "UK SAS" << "French GIGN";
    this->img_skins_tt["Seal Force"] = "assets/gfx/npc/urban}.png";
    this->img_skins_tt["German GSG-9"] = "assets/gfx/npc/gs.png";
    this->img_skins_tt["UK SAS"] = "assets/gfx/npc/sas.png";
    this->img_skins_tt["French GIGN"] = "assets/gfx/npc/gign.png";
}
QListWidget* LobbyView::create_item(QWidget* parent, const QStringList& options) {

    QListWidget* list_map = new QListWidget(parent);
    list_map->setStyleSheet(R"(
    QListWidget {
        background-color: transparent;
        border: 2px solid #444;
        border-radius: 8px;
        padding: 5px;
        color: white;
        font-size: 16px;
  })");
    QFont fuente;
    list_map->setFont(fuente);

    for (const QString& text: options) {
        list_map->addItem(text);
    }
    return list_map;
}

/*
Seccion de mostrar mapas
Este metodo en si es viejo, es mejor la version similar a skins ya que esta
cargado al crear y no al correr esta funcion el mapa
*/
void LobbyView::section_maps(QWidget* tabMap, const std::map<QString, QString>& options,
                             const QStringList& items_text) {

    QLabel* images = new QLabel();
    QLabel* selected = new QLabel();
    selected->setFixedSize(200, 25);
    selected->setAlignment(Qt::AlignCenter);
    selected->setStyleSheet(LOBBY_LABEL_STYLE2);
    QLabel* maps_names = new QLabel("Maps Names");
    maps_names->setFixedSize(200, 25);
    maps_names->setAlignment(Qt::AlignCenter);
    maps_names->setStyleSheet(LOBBY_LABEL_STYLE2);
    images->setAlignment(Qt::AlignCenter);

    QVBoxLayout* maps_layout = new QVBoxLayout();
    maps_layout->addWidget(maps_names);
    for (const QString& map_name: items_text) {
        // Options ya deberia estar cargado, no por parametro
        QPushButton* button_map = buttons_creator.create_button(
                map_name,
                [this, images, options, map_name, selected]() {
                    infoPlayer.map = map_name.toStdString();
                    QPixmap pixmap(options.at(map_name));
                    images->setPixmap(pixmap.scaled(600, 600, Qt::KeepAspectRatio));
                    selected->setText(map_name);
                },
                ITEM_STYLE);
        maps_layout->addWidget(button_map);
    }
    QVBoxLayout* info_layout = new QVBoxLayout();
    info_layout->addWidget(images);
    info_layout->addWidget(selected, 0, Qt::AlignCenter);
    info_layout->setSpacing(10);
    QHBoxLayout* final_layout = new QHBoxLayout(tabMap);
    final_layout->addLayout(maps_layout);
    final_layout->addSpacing(20);
    final_layout->addLayout(info_layout);
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

/*
FUNCIONES DE UTILIDAD
*/
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
void LobbyView::update_join_list() {
    protocol.send_list_games();
    std::vector<std::string> list = protocol.read_list_games();
    list_games->clear();
    for (const std::string& partida: list) {
        list_games->addItem(QString::fromStdString(partida));
        qDebug() << "Partida añadida:" << QString::fromStdString(partida);
    }
}
/*

ACTION HELP

*/
void LobbyView::action_help(QWidget* page_help) {

    QVBoxLayout* layout = new QVBoxLayout(page_help);

    QTextEdit* helpText = new QTextEdit(page_help);
    helpText->setReadOnly(true);

    QFont fuente("Segoe UI", 11);
    helpText->setFont(fuente);
    const QString helpHtml = R"(<style>
  body {
    color: rgb(226, 160, 160);
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    background-color: rgb(10, 10, 10);
    padding: 20px;
  }
  h2 {
    color: rgb(255, 80, 80);
    margin-bottom: 20px;
    text-shadow: 1px 1px 2px black;
  }
  .label-box {
    background-color: rgba(255, 255, 255, 0.1);
    border: 2px solid rgb(255, 80, 80);
    border-radius: 10px;
    padding: 10px 15px;
    margin: 10px 0;
    box-shadow: 0 0 8px rgba(255, 80, 80, 0.6);
    font-size: 14px;
    color: #eee;
  }
  .label-box b {
    color: rgb(255, 150, 150);
  }
  </style>

  <body>
    <h2>Bienvenido al Tutorial del Lobby</h2>
    <div class="label-box">
      <b>Join Game:</b> En la ventana de Join game tendra la posibilidad de unirse a una partida ya creada por otro jugador.
    </div>
    <div class="label-box">
      <b>Create Game:</b> En la ventana de Create Game podra crear usted mismo su partida!.
    <table>
    H
    <h2> Como unirse o crear una partida </h2>
    <thead>
      <tr>
        <th>Unirse a una partida</th>
        Al unirse a una partida debera de indicar su nombre, y las skins que quiera tener en el momento de jugar
      </tr>
      <tr>
        <th>Crear una partida</th>
        Al crear una partida debera de indicar el mapa con el cual su partida se creara, luego sera igual que al unirse a una partida.
      </tr>
    </thead>
  </table>
  <img src="assets/gfx/screens/promotional.jpg" width="500" height="auto" />
  </body>)";
    helpText->setHtml(helpHtml);

    layout->addWidget(helpText);
}

void LobbyView::add_help_page(QWidget* page_help) {
    QVBoxLayout* layout = new QVBoxLayout(page_help);
    QWidget* container = new QWidget();
    layout->addWidget(container);
    // Aca agregamos el boton de help
    QPushButton* back_button = buttons_creator.create_button(
            "Back", [this]() { this->stack_navigator.back(); }, LOBBY_STYLE);
    action_help(container);  // Aca seteamos la pagina en si
    layout->addWidget(back_button);
    stack_navigator.add_widget(page_help);
    return;
}

/*

ACTION UNIRSE / CREAR JUGADOR

*/

void LobbyView::section_skins(QVBoxLayout* selection) {
    // Quiza que no sean CBox
    QHBoxLayout* h_layout = new QHBoxLayout();
    h_layout->setAlignment(Qt::AlignCenter);
    QFormLayout* tt_column = new QFormLayout();
    QFormLayout* ct_column = new QFormLayout();
    QLabel* ct_text = new QLabel("CounterTerrorist skins");
    QLabel* tt_text = new QLabel("Terrorist skins");
    ct_text->setStyleSheet(LOBBY_LABEL_STYLE2);
    tt_text->setStyleSheet(LOBBY_LABEL_STYLE2);
    ct_text->setFixedSize(200, 50);
    tt_text->setFixedSize(200, 50);
    QLabel* ct_img = new QLabel();
    QLabel* tt_img = new QLabel();
    tt_img->setAlignment(Qt::AlignCenter);
    ct_img->setAlignment(Qt::AlignCenter);

    tt_img->setFixedSize(300, 300);
    ct_img->setFixedSize(300, 300);
    QComboBox* combo_terrorist = new QComboBox();
    QComboBox* combo_counter_terrorist = new QComboBox();
    combo_terrorist->setStyleSheet(LOBBY_COMBO_STYLE);
    combo_counter_terrorist->setStyleSheet(LOBBY_COMBO_STYLE);
    for (const auto& skins: this->img_skins_tt) combo_terrorist->addItem(skins.first);
    for (const auto& skins: this->img_skins_ct) combo_counter_terrorist->addItem(skins.first);
    ct_column->addWidget(ct_text);
    ct_column->addRow(combo_counter_terrorist);
    tt_column->addWidget(tt_text);
    tt_column->addRow(combo_terrorist);
    tt_column->addWidget(tt_img);
    ct_column->addWidget(ct_img);
    h_layout->addLayout(tt_column);
    h_layout->addStretch(1);
    h_layout->addLayout(ct_column);
    selection->addLayout(h_layout);
    connect(combo_terrorist, &QComboBox::currentTextChanged, [this, tt_img](const QString& skin) {
        infoPlayer.skin2 = skin.toStdString();
        QPixmap pixmap(this->img_skins_tt.at(skin));  // Recordatorio, Pixmap es la img en path
        tt_img->setPixmap(pixmap.scaled(300, 300, Qt::KeepAspectRatio));
    });
    connect(combo_counter_terrorist, &QComboBox::currentTextChanged,
            [this, ct_img](const QString& skin) {
                infoPlayer.skin = skin.toStdString();
                // Recordatorio, Pixmap es la img en path
                QPixmap pixmap(this->img_skins_ct.at(skin));
                ct_img->setPixmap(pixmap.scaled(300, 300, Qt::KeepAspectRatio));
            });
    // Aca seteamos la primera img
    QPixmap ct_default(img_skins_ct.begin()->second);
    ct_img->setPixmap(ct_default.scaled(300, 300, Qt::KeepAspectRatio));
    QPixmap tt_default(this->img_skins_tt.begin()->second);
    tt_img->setPixmap(tt_default.scaled(300, 300, Qt::KeepAspectRatio));
}
void LobbyView::add_player_page(QWidget* page_player) {
    QVBoxLayout* layout = new QVBoxLayout(page_player);
    QPushButton* back_button = buttons_creator.create_button(
            "Back", [this]() { this->stack_navigator.back(); }, LOBBY_STYLE);
    QLabel* name_player = new QLabel("NickName: ");
    name_player->setStyleSheet(LOBBY_LABEL_STYLE2);
    name_player->setFixedSize(200, 50);
    QLineEdit* name = new QLineEdit();
    connect(name, &QLineEdit::textChanged, this,
            [&](const QString& text) { this->infoPlayer.info.name_player = text.toStdString(); });
    layout->addWidget(name_player);
    layout->addWidget(name);
    section_skins(layout);  // Aca viene la seleccion de skins
    QPushButton* play_button = buttons_creator.create_button(
            "Play",
            [this]() {
                if (this->infoPlayer.info.name_player.empty()) {
                    QMessageBox::warning(nullptr, "Empty name", "No tenes ningun nickname");
                    return;
                }
                if (this->modo_lobby_actual == LobbyMode::JOIN)
                    this->function_join();
                else
                    this->function_create();
            },
            LOBBY_STYLE);
    QHBoxLayout* options = new QHBoxLayout();
    options->addWidget(back_button);
    options->addStretch();
    options->addWidget(play_button);
    layout->addLayout(options);
    stack_navigator.add_widget(page_player);
    return;
}

/*
VENTANAS DE CREATE Y JOIN
*/
void LobbyView::configure_window_join(QWidget* window_join) {
    QStringList options;
    QVBoxLayout* layout = new QVBoxLayout(window_join);

    QPushButton* help_button = buttons_creator.create_button(
            "Tutorial", [this]() { this->stack_navigator.go_to(this->page_help); }, LOBBY_STYLE);

    QPushButton* back_button = buttons_creator.create_button(
            "Back", [this]() { this->stack_navigator.back(); }, LOBBY_STYLE);

    // Lista de partidas aca
    QWidget* formWidget = new QWidget(window_join);
    this->list_games = create_item(window_join, options);
    connect(this->list_games, &QListWidget::itemClicked, [this, options](QListWidgetItem* item) {
        qDebug() << item->text();
        infoPlayer.info.name_game = item->text().toStdString();
    });
    //
    QHBoxLayout* h_box = new QHBoxLayout();
    layout->addWidget(list_games);
    layout->addWidget(formWidget);
    buttons_creator.add_button(
            layout, BUTTON_JOIN,
            [this]() {
                if (this->infoPlayer.info.name_game.empty()) {
                    QMessageBox::warning(nullptr, "Empty name", "No seleccionaste ninguna partida");
                    return;
                }
                this->modo_lobby_actual = LobbyMode::JOIN;
                this->stack_navigator.go_to(this->page_player_select);
            },
            LOBBY_STYLE);
    h_box->addWidget(back_button, 0, Qt::AlignLeft);
    h_box->addStretch();
    h_box->addWidget(help_button, 0, Qt::AlignRight);
    layout->addLayout(h_box);
}
void LobbyView::configure_window_create(QWidget* window_create) {
    QVBoxLayout* layout = new QVBoxLayout(window_create);
    QPushButton* help_button = buttons_creator.create_button(
            "Help", [this]() { this->stack_navigator.go_to(this->page_help); }, LOBBY_STYLE);
    QPushButton* back_button = buttons_creator.create_button(
            "Back", [this]() { this->stack_navigator.back(); }, LOBBY_STYLE);
    QLabel* set_name = new QLabel("New Game Name");
    set_name->setAlignment(Qt::AlignCenter);
    set_name->setFixedSize(200, 25);
    set_name->setStyleSheet(LOBBY_LABEL_STYLE2);
    QLineEdit* input_name = new QLineEdit();
    connect(input_name, &QLineEdit::textChanged, this,
            [&](const QString& text) { this->infoPlayer.info.name_game = text.toStdString(); });
    layout->addWidget(set_name);
    layout->addWidget(input_name);
    QWidget* maps = new QWidget();
    section_maps(maps, img_maps, options_map);
    layout->addWidget(maps);
    buttons_creator.add_button(
            layout, BUTTON_CREATE,
            [this]() {
                if (this->infoPlayer.info.name_game.empty()) {
                    QMessageBox::warning(nullptr, "Empty name",
                                         "No seleccionaste ningun nombre de partida");
                    return;
                } else if (this->infoPlayer.map.empty()) {
                    QMessageBox::warning(nullptr, "Empty map", "No seleccionaste ningun mapa");
                    return;
                }
                // Aca alertas de que pasa si no pusiste nombre ni seleccionaste mapa
                this->modo_lobby_actual = LobbyMode::CREATE;
                this->stack_navigator.go_to(this->page_player_select);
            },
            LOBBY_STYLE);
    QHBoxLayout* h_box = new QHBoxLayout();
    h_box->addWidget(back_button, 0, Qt::AlignLeft);
    h_box->addStretch();
    h_box->addWidget(help_button, 0, Qt::AlignRight);
    layout->addLayout(h_box);
}

/*
EL INICIO DE PLAY SERIA ESTE
*/
void LobbyView::play_game(QTabWidget* page_play) {
    this->page_player_select = new QWidget();
    this->page_player_select->setStyleSheet(PAGE_PLAYER_STYLE);
    this->page_help = new QWidget();
    add_player_page(this->page_player_select);
    add_help_page(this->page_help);
    QWidget* window_join = new QWidget();
    QWidget* window_create = new QWidget();
    page_play->addTab(window_join, "Join Game");
    page_play->addTab(window_create, "Create Game");
    configure_window_join(window_join);
    configure_window_create(window_create);
}

LobbyView::~LobbyView() {}
