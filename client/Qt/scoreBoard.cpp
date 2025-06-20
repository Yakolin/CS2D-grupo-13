#include "scoreBoard.h"

#include <QFormLayout>
#include <QHeaderView>
#include <QLabel>
#include <QTableWidget>
#include <QGridLayout>
#include <QWidget>
#include <QtCharts/qchartview.h>

ScoreBoard::ScoreBoard(): scores(), ranking_group() {
    scores[1] = {"player1", "CT", 10, 2, 100, 100};
    scores[2] = {"player2", "TT", 5, 1, 50, 90};
    scores[3] = {"player3", "CT", 8, 3, 80, 75};
    scores[4] = {"player4", "TT", 12, 4, 120, 60};
    scores[5] = {"player5", "CT", 7, 2, 90, 80};
    scores[6] = {"player6", "TT", 6, 3, 60, 85};
    scores[7] = {"player7", "CT", 9, 1, 110, 95};
    scores[8] = {"player8", "TT", 4, 2, 40, 70};
    scores[9] = {"player9", "CT", 11, 5, 130, 88};
    scores[10] = {"player10", "TT", 3, 0, 30, 65};

    ranking_group.ranking_counter_terrorists = 34;
    ranking_group.ranking_terrorists = 12;
}

void ScoreBoard::add_table(QGridLayout* layout, const int& fil, const int& col) {
    QTableWidget* table = new QTableWidget(scores.size(), 6);
    table->setHorizontalHeaderLabels({"Player ID", "Name", "Kills", "Deaths", "Collected Money", "Points"});

    int fila = 0;
    for (const auto& [id, summary] : scores) {
        table->setItem(fila, 0, new QTableWidgetItem(QString::number(id)));
        table->setItem(fila, 1, new QTableWidgetItem(QString::fromStdString(summary.name_player)));
        table->setItem(fila, 2, new QTableWidgetItem(QString::number(summary.kills)));
        table->setItem(fila, 3, new QTableWidgetItem(QString::number(summary.deaths)));
        table->setItem(fila, 4, new QTableWidgetItem(QString::number(summary.collected_money)));
        table->setItem(fila, 5, new QTableWidgetItem(QString::number(summary.puntos)));
        fila++;
    }
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(table, fil, col, 1, -1); // filas 1, columna 0, colspan = toda la fila
}


void ScoreBoard::add_chart(QGridLayout* layout,const int& fil,const int& col) {
    QtCharts::QBarSeries* series = new QtCharts::QBarSeries();

    QStringList categories;
    QtCharts::QBarSet* set = new QtCharts::QBarSet("Puntos");

    for (const auto& [id, summary] : scores) {
        categories << QString::fromStdString(summary.name_player);
        *set << summary.puntos;
    }

    series->append(set);

    QtCharts::QChart* chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Puntos por jugador");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QBarCategoryAxis* axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QtCharts::QValueAxis* axisY = new QtCharts::QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QtCharts::QChartView* chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView, fil, col, 1, -1); // debajo de todo
}

void style(QTableWidget* table){
    table->setStyleSheet(
        "QTableWidget {"
        "  border: 2px solid gray;"
        "  border-radius: 10px;"
        "  background-color: white;"
        "  padding: 5px;"
        "}"
        "QHeaderView::section {"
        "  background-color: lightgray;"
        "  padding: 4px;"
        "  border: none;"
        "}"
    );

}
void ScoreBoard::add_filtered_tables(QGridLayout* layout) {

    QTableWidget* ct_table = new QTableWidget(0, 6);
    QTableWidget* tt_table = new QTableWidget(0, 6);

    QStringList headers = {"Player ID", "Name", "Kills", "Deaths", "Collected Money", "Points"};
    ct_table->setHorizontalHeaderLabels(headers);
    tt_table->setHorizontalHeaderLabels(headers);

    // Filtrar el mapa `scores` por equipo
    for (const auto& [id, summary] : scores) {
        QTableWidget* table = nullptr;
        if (summary.team == "CT") {
            int row = ct_table->rowCount();
            ct_table->insertRow(row);
            table = ct_table;
        } else if (summary.team == "TT") {
            int row = tt_table->rowCount();
            tt_table->insertRow(row);
            table = tt_table;
        }
        style(table);
        if (table) {
            int row = table->rowCount() - 1;
            table->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
            table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(summary.name_player)));
            table->setItem(row, 2, new QTableWidgetItem(QString::number(summary.kills)));
            table->setItem(row, 3, new QTableWidgetItem(QString::number(summary.deaths)));
            table->setItem(row, 4, new QTableWidgetItem(QString::number(summary.collected_money)));
            table->setItem(row, 5, new QTableWidgetItem(QString::number(summary.puntos)));
        }
    }

    ct_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tt_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Etiquetas
    QLabel* ct_label = new QLabel("Counter-Terrorists");
    QLabel* tt_label = new QLabel("Terrorists");

    // Mostrar tablas en el layout
    layout->addWidget(ct_label, 0, 0);
    layout->addWidget(ct_table, 1, 0);
    layout->addWidget(tt_label, 0, 1);
    layout->addWidget(tt_table, 1, 1);
}

void ScoreBoard::add_ranking(QGridLayout* layout, const int& fil, const int& col) {
    QFormLayout* rankingGroups = new QFormLayout;

    QLabel* label_terrorists = new QLabel(QString::number(ranking_group.ranking_terrorists));
    rankingGroups->addRow(new QLabel("Terrorists:"), label_terrorists);

    QLabel* label_counter_terrorists = new QLabel(QString::number(ranking_group.ranking_counter_terrorists));
    rankingGroups->addRow(new QLabel("Counter-terrorists:"), label_counter_terrorists);

    layout->addLayout(rankingGroups, fil, col); // fila 0, columna 0
}

QChartView* ScoreBoard::grafico_pie(QWidget* parent) {
    // Sumar puntos por equipo
    int puntos_ct = 0;
    int puntos_tt = 0;
    for (const auto& [id, summary] : scores) {
        if (summary.team == "CT") {
            puntos_ct += summary.puntos;
        } else if (summary.team == "TT") {
            puntos_tt += summary.puntos;
        }
    }

    QtCharts::QPieSeries* series = new QtCharts::QPieSeries();
    series->append("CT", puntos_ct);
    series->append("TT", puntos_tt);

    QtCharts::QChart* chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Distribución de puntos por equipo");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QChartView* chartView = new QChartView(chart, parent);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}

QChartView* ScoreBoard::graficoBarrasEquipo(const std::string& equipo, QWidget* parent) {
    using namespace QtCharts;

    QBarSet* killsSet = new QBarSet("Kills");
    QBarSet* deathsSet = new QBarSet("Deaths");
    QBarSet* moneySet = new QBarSet("Money");
    QBarSet* pointsSet = new QBarSet("Points");

    int totalKills = 0, totalDeaths = 0, totalMoney = 0, totalPoints = 0;

    for (const auto& [id, summary] : scores) {
        if (summary.team == equipo) {
            totalKills += summary.kills;
            totalDeaths += summary.deaths;
            totalMoney += summary.collected_money;
            totalPoints += summary.puntos;
        }
    }

    *killsSet << totalKills;
    *deathsSet << totalDeaths;
    *moneySet << totalMoney;
    *pointsSet << totalPoints;

    QBarSeries* series = new QBarSeries();
    series->append(killsSet);
    series->append(deathsSet);
    series->append(moneySet);
    series->append(pointsSet);

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(QString::fromStdString("Estadísticas de equipo ") + QString::fromStdString(equipo));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << QString::fromStdString(equipo);
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    
    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Valor");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    
    QChartView* chartView = new QChartView(chart, parent);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}


int ScoreBoard::show_scores_game() {
    QWidget* info_ranking = new QWidget();
    info_ranking->setWindowTitle("Scores");
    info_ranking->resize(800, 500);
    QGridLayout* mainLayout = new QGridLayout(info_ranking);
    add_filtered_tables(mainLayout);
    mainLayout->addWidget(graficoBarrasEquipo("CT", info_ranking), 2, 0);
    mainLayout->addWidget(graficoBarrasEquipo("TT", info_ranking), 2, 1);
    // (Opcional) Gráfico pie al centro o en una 3ra columna
    // mainLayout->addWidget(grafico_pie(info_ranking), 2, 2);
    info_ranking->show();
    return 0;
}

ScoreBoard::~ScoreBoard() {}
