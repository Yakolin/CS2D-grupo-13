#include "vista.h"

const int HEIGHT_MENU = 500;
const int WIDTH_MENU = 500;

int Vista::menu() {

    static QMainWindow mainWindow;
    mainWindow.setWindowTitle("Counter Strike");
    mainWindow.setStyleSheet("background-color:rgb(188, 101, 132);"); 
    mainWindow.resize(WIDTH_MENU, HEIGHT_MENU);

    QWidget *centralWidget = new QWidget(&mainWindow);
    mainWindow.setCentralWidget(centralWidget);
    
    QVBoxLayout *h_table = new QVBoxLayout(centralWidget);

    QPushButton *button_crear = new QPushButton("Crear Partida", &mainWindow);
    QPushButton *button_unirse = new QPushButton("Unirse a Partida", &mainWindow);
    button_crear->setFixedSize(200, 50);
    button_unirse->setFixedSize(200, 50);


    h_table->addWidget(button_crear);
    h_table->addWidget(button_unirse);
    

    QObject::connect(button_crear, &QPushButton::clicked, [&]() {
        QMessageBox::information(&mainWindow, "Mensaje", "se creó una partida");
    });
    QObject::connect(button_unirse, &QPushButton::clicked, [&]() {
        QMessageBox::information(&mainWindow, "Mensaje", "se unió a una partida");
    });

    mainWindow.show();
    return 0;

}

QLabel* Vista::cell(const QString &text, const bool& bold) {
    QLabel *label = new QLabel(bold ? "<b>" + text + "</b>" : text);
    label->setStyleSheet("border: 1px solid black; padding: 4px;");
    label->setAlignment(Qt::AlignCenter);
    return label;
}


void Vista::add_table(QVBoxLayout *scores_table, const std::map<std::string, PlayerSummary>& scores){

    int cols = scores.size();
    QTableWidget *table = new QTableWidget(scores.size(), 4);
    table->verticalHeader()->setVisible(false);
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

    scores_game(scores, ranking);
    app.exec();
    return 0;
}

