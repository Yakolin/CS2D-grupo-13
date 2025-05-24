#include "scoreBoard.h"

#include <QFormLayout>
#include <QHeaderView>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <map>
#include <string>
ScoreBoard::ScoreBoard(): scores(), ranking_group() {
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

    ranking_group.ranking_counter_terrorists = 34;
    ranking_group.ranking_terrorists = 12;
}


void ScoreBoard::add_table(QVBoxLayout* scores_table) {

    QTableWidget* table = new QTableWidget(scores.size(), 4);
    // table->verticalHeader()->setVisible(false);
    table->setHorizontalHeaderLabels({"Player", "Kill", "Dead", "Collected Money"});

    int fil = 0;
    for (const auto& [player_name, summary]: scores) {

        table->setItem(fil, 0, new QTableWidgetItem(QString::fromStdString(player_name)));
        table->setItem(fil, 1,
                       new QTableWidgetItem(QString::fromStdString(std::to_string(summary.kills))));
        table->setItem(
                fil, 2,
                new QTableWidgetItem(QString::fromStdString(std::to_string(summary.deaths))));
        table->setItem(fil, 3,
                       new QTableWidgetItem(
                               QString::fromStdString(std::to_string(summary.collected_money))));
        fil++;
    }
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    scores_table->addWidget(table);
}

void ScoreBoard::add_ranking(QVBoxLayout* scores_table) {

    QFormLayout* ranking_groups = new QFormLayout;

    QLabel* label_terrorists =
            new QLabel(QString::fromStdString(std::to_string(ranking_group.ranking_terrorists)));
    ranking_groups->addRow(new QLabel("terrorists: "), label_terrorists);

    QLabel* label_counter_terrorists = new QLabel(
            QString::fromStdString(std::to_string(ranking_group.ranking_counter_terrorists)));
    ranking_groups->addRow(new QLabel("counter-terrorists: "), label_counter_terrorists);

    scores_table->addLayout(ranking_groups);
}

int ScoreBoard::show_scores_game() {

    QWidget* info_ranking = new QWidget();
    info_ranking->setWindowTitle("Scores");
    info_ranking->setStyleSheet("background-color:rgb(160, 188, 194);");
    info_ranking->resize(500, 500);

    QVBoxLayout* scores_table = new QVBoxLayout(info_ranking);

    add_table(scores_table);
    add_ranking(scores_table);

    info_ranking->setLayout(scores_table);
    info_ranking->show();

    return 0;
}

ScoreBoard::~ScoreBoard() {}
