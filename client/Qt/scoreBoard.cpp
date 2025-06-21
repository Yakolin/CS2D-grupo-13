#include "scoreBoard.h"

#include <QFormLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QTableWidget>
#include <QWidget>

#include <QtCharts/qchartview.h>


ScoreBoard::ScoreBoard(const std::map<player_id_t, InfoPlayer>& table): scores(table) {
}

void ScoreBoard::add_table(QGridLayout* layout, const int& fil, const int& col) {
    QTableWidget* table = new QTableWidget(scores.size(), 6);
    table->setHorizontalHeaderLabels({"Player ID", "Name", "Points", "Deaths"});

    int fila = 0;
    for (const auto& [id, summary]: scores) {
        table->setItem(fila, 0, new QTableWidgetItem(QString::number(id)));
        //table->setItem(fila, 1, new QTableWidgetItem(QString::fromStdString(summary.name_player)));
        table->setItem(fila, 2, new QTableWidgetItem(QString::number(summary.puntos)));
        table->setItem(fila, 3, new QTableWidgetItem(QString::number(summary.deaths)));
        fila++;
    }
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(table, fil, col, 1, -1);  // filas 1, columna 0, colspan = toda la fila
}


void ScoreBoard::add_chart(QGridLayout* layout, const int& fil, const int& col) {
    QtCharts::QBarSeries* series = new QtCharts::QBarSeries();

    QStringList categories;
    QtCharts::QBarSet* set = new QtCharts::QBarSet("Puntos");

    for (const auto& [id, summary]: scores) {
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

    layout->addWidget(chartView, fil, col, 1, -1);  // debajo de todo
}

void style(QTableWidget* table) {
    table->setStyleSheet(
            "QTableWidget {"
            "  background-color: rgb(36, 36, 36); color: rgb(255, 255, 255); font-size: 14px;      \
   font-weight: bold;border-radius: 25px;padding: 8px 16px; border: 2px solid rgb(0, 132, 255);"
            "}"
            "QHeaderView::section {background-color:rgb(36, 36, 36) ; color: rgb(255, 255, 255); "
            "font-size: 14px;}");
}
void ScoreBoard::add_filtered_tables(QGridLayout* layout) {

    QTableWidget* ct_table = new QTableWidget(0, 4);
    QTableWidget* tt_table = new QTableWidget(0, 4);

    QStringList headers = {"Player ID", "Points", "Deaths"};
    ct_table->setHorizontalHeaderLabels(headers);
    tt_table->setHorizontalHeaderLabels(headers);

    // Filtrar el mapa `scores` por equipo
    for (const auto& [id, summary]: scores) {
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
          //  table->setItem(row, 1,new QTableWidgetItem(QString::fromStdString(summary.name_player)));
            table->setItem(row, 2, new QTableWidgetItem(QString::number(summary.puntos)));
            table->setItem(row, 3, new QTableWidgetItem(QString::number(summary.deaths)));
        }
    }

    ct_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tt_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ct_table->verticalHeader()->setVisible(false);
    tt_table->verticalHeader()->setVisible(false);
    // Etiquetas
    QLabel* ct_label = new QLabel("Counter-Terrorists");
    QLabel* tt_label = new QLabel("Terrorists");
    ct_label->setStyleSheet(LOBBY_LABEL_STYLE2);
    tt_label->setStyleSheet(LOBBY_LABEL_STYLE2);

    // Mostrar tablas en el layout
    layout->addWidget(ct_label, 0, 0);
    layout->addWidget(ct_table, 1, 0);
    layout->addWidget(tt_label, 0, 1);
    layout->addWidget(tt_table, 1, 1);
}


QChartView* ScoreBoard::grafico_pie(QWidget* parent) {
    // Sumar puntos por equipo
    int puntos_ct = 0;
    int puntos_tt = 0;
    for (const auto& [id, summary]: scores) {
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
    QBarSet* deathsSet = new QBarSet("Deaths");
    QBarSet* pointsSet = new QBarSet("Points");

    int totalDeaths = 0, totalPoints = 0;

    for (const auto& [id, summary]: scores) {
        if (summary.team == equipo) {
            totalDeaths += summary.deaths;
            totalPoints += summary.puntos;
        }
    }

    *deathsSet << totalDeaths;
    *pointsSet << totalPoints;

    QBarSeries* series = new QBarSeries();
    series->append(deathsSet);
    series->append(pointsSet);

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(QString::fromStdString("Estadísticas de equipo ") +
                    QString::fromStdString(equipo));
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
    info_ranking->setStyleSheet("QWidget { background-color: rgb(36, 36, 36); color: rgb(255, 255, "
                                "255); font-size: 14px;}");
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
