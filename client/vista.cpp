#include "vista.h"

const int HEIGHT_MENU = 500;
const int WIDTH_MENU = 500;

void Vista::add_button(QVBoxLayout *layout, const QString &text, const std::function<void()> &action) {

    QPushButton *button = new QPushButton(text );
    button->setFixedSize(200, 50);
    QObject::connect(button, &QPushButton::clicked, action);
    layout->addWidget(button,0, Qt::AlignHCenter);
}

void Vista::add_sub_options( QTreeWidgetItem *parent , const QString &text) {
    QTreeWidgetItem *map1 = new QTreeWidgetItem(parent);
    QFont fuente;
    fuente.setPointSize(12);
    fuente.setBold(false);
    fuente.setFamily("Arial");
    map1->setFont(0, fuente);
    map1->setText(0, text);
}

void Vista::create_item( QTreeWidget *parent , const QStringList &options, const QString &text) {

    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    QFont fuente;
    fuente.setPointSize(14);
    fuente.setBold(true);
    item->setFont(0, fuente);
    item->setText(0, text);

    for (const QString &text : options) {
        add_sub_options(item, text);
    }
}

void Vista::config_windows(QWidget *ventana, const QString &text, int width, int height) {
    ventana->setWindowTitle(text);
    ventana->setStyleSheet("background-color:rgb(71, 75, 75);");
    ventana->resize(width, height);
}


void Vista::action_create() {

    QTabWidget *tabs = new QTabWidget();
    tabs->setWindowTitle("Create Game");
    tabs->setStyleSheet("background-color:rgb(50, 58, 58);");
    tabs->resize(500, 500);
    tabs->setTabShape(QTabWidget::Rounded);
    tabs->setTabsClosable(false);
    tabs->setMovable(true);

    QLabel *label = new QLabel();

    QWidget *tabMap = new QWidget();
    QWidget *tabOptions = new QWidget();
    QWidget *tabPlayers = new QWidget();

    tabs->addTab(tabMap, "Map");
    tabs->addTab(tabOptions, "Options");
    tabs->addTab(tabPlayers, "Players");

    QListWidget *list_map = new QListWidget(tabMap);
    list_map->addItem("Desierto");
    list_map->addItem("Pueblito Azteca");
    list_map->addItem("Zona de Entrenamiento");

    QListWidget *list_options = new QListWidget(tabPlayers);
    list_options->addItem("Phoenix");
    list_options->addItem("L337 Krew");
    list_options->addItem("Arctic Avenger");
    list_options->addItem("Guerrilla");
    QListWidget *list_unidad = new QListWidget(tabOptions);
    list_unidad->addItem("Seal Force");
    list_unidad->addItem("German GSG-9");
    list_unidad->addItem("UK SAS");
    list_unidad->addItem("French GIGN");

    QHBoxLayout *layoutMap = new QHBoxLayout(tabMap);
    layoutMap->addWidget(label);
    layoutMap->addWidget(list_map);

    QListWidgetItem *selected = nullptr;


    connect(list_map, &QListWidget::itemClicked, [label, &selected](QListWidgetItem *item){
    QString nombre = item->text();
    selected = item;

    if (nombre == "Desierto")
        label->setPixmap(QPixmap("../assets/gfx/tiles/default_inferno.png"));
    else if (nombre == "Pueblito Azteca")
        label->setPixmap(QPixmap("../assets/gfx/tiles/default_aztec.png"));
    else if (nombre == "Zona de Entrenamiento")
        label->setPixmap(QPixmap("../assets/gfx/tiles/default_dust.png"));
    });



    //QStringList options_map = {"Desierto", "Pueblito Azteca", "Zona de Entrenamiento"};
    //QStringList options_skins = {"Phoenix", "L337 Krew", "Arctic Avenger", "Guerrilla"};
    //QStringList options_unidad = {"Seal Force", "German GSG-9", "UK SAS", "French GIGN"};

    tabs->show();
}

void Vista::action_join() {
    QMessageBox::information(nullptr, "Mensaje", "Se unió a una partida");
}

void Vista::action_exit() {
    QMessageBox::StandardButton answer = QMessageBox::question(nullptr, "Mensaje", "Desea salir?");
    if (answer == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void Vista::action_help() {

    QString ayuda = "<b>create game</b><br>"
                "para crear una nueva partida<br>"
                "<b>join game</b><br>"
                "para unirse a una partida existente<br>"
                "<b>exit</b><br>"
                "para salir";
    QMessageBox msgBox;
    msgBox.setWindowTitle("Help");
    msgBox.setText(ayuda);

    msgBox.setStyleSheet("background-color:rgb(90, 94, 94); color: black");

    msgBox.exec();

}



int Vista::menu() {

    QMainWindow *menu = new QMainWindow();
    menu->setWindowTitle("Counter Strike");
    menu->resize(500, 500);

    QLabel *map = new QLabel();
    map->setPixmap(QPixmap("../assets/gfx/cs2d.png"));

    QWidget *central = new QWidget(menu);
    central->setStyleSheet("background-color:rgb(92, 95, 95);");
    menu->setCentralWidget(central);

    QVBoxLayout *layout = new QVBoxLayout();
    QPixmap pixmap("../assets/gfx/cs2d.png");
    QLabel *img_icono = new QLabel();
    img_icono->setPixmap(pixmap);
    img_icono->setFixedSize(100, 100);
    img_icono->setAlignment(Qt::AlignCenter);
    
    layout->addWidget(img_icono, 0, Qt::AlignCenter);
    add_button(layout, "create game", [this]() { this->action_create(); });
    add_button(layout, "join game",   [this]() { this->action_join(); });
    add_button(layout, "Help",        [this]() { this->action_help(); });
    add_button(layout, "exit game",   [this]() { this->action_exit(); });

    central->setLayout(layout);

    menu->show();

    return 0;

}

QLabel* Vista::cell(const QString &text, const bool& bold) {
    QLabel *label = new QLabel(bold ? "<b>" + text + "</b>" : text);
    label->setStyleSheet("border: 1px solid black; padding: 4px;");
    label->setAlignment(Qt::AlignCenter);
    return label;
}


void Vista::add_table(QVBoxLayout *scores_table, const std::map<std::string, PlayerSummary>& scores){

    QTableWidget *table = new QTableWidget(scores.size(), 4);
    //table->verticalHeader()->setVisible(false);
    table->setHorizontalHeaderLabels({"Player", "Kill", "Dead", "Collected Money"});

    int fil = 0;
    for (const auto& [player_name, summary] : scores){

        table->setItem(fil, 0, new QTableWidgetItem(QString::fromStdString(player_name)));
        table->setItem(fil, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(summary.kills))));
        table->setItem(fil, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(summary.deaths))));
        table->setItem(fil, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(summary.collected_money))));
        fil++;
    }
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    scores_table->addWidget(table);


}

void Vista::add_ranking(QVBoxLayout *scores_table, Rankings& ranking) {

    QFormLayout *ranking_group = new QFormLayout;

    QLabel *label_terrorists = new QLabel(QString::fromStdString(std::to_string(ranking.ranking_terrorists)));
    ranking_group->addRow(new QLabel("terrorists: "), label_terrorists);

    QLabel *label_counter_terrorists = new QLabel(QString::fromStdString(std::to_string(ranking.ranking_counter_terrorists)));
    ranking_group->addRow(new QLabel("counter-terrorists: "), label_counter_terrorists);

    scores_table->addLayout(ranking_group);

}

int Vista::scores_game(const std::map<std::string, PlayerSummary>& scores, Rankings& ranking) {

    QWidget *info_ranking = new QWidget();
    info_ranking->setWindowTitle("Scores");
    info_ranking->setStyleSheet("background-color:rgb(160, 188, 194);");
    info_ranking->resize(500, 500);

    QVBoxLayout* scores_table = new QVBoxLayout(info_ranking);
    add_table(scores_table, scores);
    add_ranking(scores_table, ranking);

    info_ranking->setLayout(scores_table);
    info_ranking->show();

    return 0;
}

int Vista::run( int& argc,  char *argv[]) {
    QApplication app(argc, argv);

    std::map<std::string, PlayerSummary> scores;
    scores["player1"] = {10, 2, 100};
    scores["player2"] = {5, 1, 50};
    scores["player3"] = {8, 3, 80};
    scores["player4"] = {12, 4, 120};
    scores["player5"] = {15, 5, 150};
    scores["player6"] = {20, 6, 200};
    scores["player7"] = {25, 7, 250};
    scores["player8"] = {30, 8, 300};
    scores["player9"] = {35, 9, 350};
    scores["player10"] = {40, 10, 400};

    Rankings ranking;
    ranking.ranking_counter_terrorists = 34;
    ranking.ranking_terrorists = 12;

    //menu();
    action_create();
    //scores_game(scores, ranking);
    app.exec();
    return 0;
}

