#include "scoreBoard.h"

#include <QFormLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QTableWidget>
#include <QWidget>
#include <QtCharts/qchartview.h>


ScoreBoard::ScoreBoard(const std::map<player_id_t, InfoPlayer>& table): scores(table) {}


void ScoreBoard::style(QTableWidget* table) {
    table->setStyleSheet(
            "QTableWidget {"
            "  background-color: rgb(36, 36, 36); color: rgb(255, 255, 255); font-size: 14px;      \
   font-weight: bold;border-radius: 25px;padding: 8px 16px; border: 2px solid rgb(0, 132, 255);"
            "}"
            "QHeaderView::section {background-color:rgb(36, 36, 36) ; color: rgb(255, 255, 255); "
            "font-size: 14px;}");
}

void ScoreBoard::staly_chart( QChart* chart,QBarCategoryAxis* axisX, QValueAxis* axisY){

    chart->setBackgroundBrush(QBrush(Qt::black));
    chart->setPlotAreaBackgroundBrush(QBrush(Qt::black));
    chart->setPlotAreaBackgroundVisible(true);
    QPen whitePen(Qt::white);
    axisX->setLabelsBrush(Qt::white);
    axisX->setTitleBrush(Qt::white);
    axisX->setLinePen(whitePen);
    axisX->setGridLinePen(QPen(Qt::darkGray));
    axisY->setLabelsBrush(Qt::white);
    axisY->setTitleBrush(Qt::white);
    axisY->setLinePen(whitePen);
    axisY->setGridLinePen(QPen(Qt::darkGray));
    chart->setTitleBrush(Qt::white);
    if (chart->legend()) {
        chart->legend()->setLabelColor(Qt::white);
        chart->legend()->setBrush(QBrush(Qt::black));
    }
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
    axisY->setTitleText("valores");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    staly_chart(chart,axisX,axisY);
    QChartView* chartView = new QChartView(chart, parent);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}

void ScoreBoard::filter_table(std::map<player_id_t, InfoPlayer>& cts,std::map<player_id_t, InfoPlayer>& tts){
    
    for( const auto& [id, summary]: scores){
        if(summary.team == "CT"){
            cts[id] = summary;
        }else{
            tts[id] = summary;
        }
    }
}

QWidget* ScoreBoard::add_table(std::map<player_id_t, InfoPlayer>& score_table, const QString& title) {
    
    QVBoxLayout* layout = new QVBoxLayout;
    QLabel* title_table = new QLabel(title);
    title_table->setAlignment(Qt::AlignCenter);
    layout->addWidget(title_table);
    title_table->setStyleSheet(LOBBY_LABEL_STYLE2);

    QTableWidget* table = new QTableWidget(score_table.size(), 5);
    table->setHorizontalHeaderLabels({"Player ID", "Deaths","Kills","collected_money","Points"});
    
    int fila = 0;
    for (const auto& [id, summary]: score_table) {
        table->setItem(fila, 0, new QTableWidgetItem(QString::number(id)));
        table->setItem(fila, 1, new QTableWidgetItem(QString::number(summary.deaths)));
        table->setItem(fila, 2, new QTableWidgetItem(QString::number(summary.kills)));
        table->setItem(fila, 3, new QTableWidgetItem(QString::number(summary.collected_money)));
        table->setItem(fila, 4, new QTableWidgetItem(QString::number(summary.puntos)));
        fila++;
    }

    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSortingEnabled(true);

    style(table);

    layout->addWidget(table);

    QWidget* container = new QWidget;
    container->setLayout(layout);
    return container;
}

int ScoreBoard::show_scores_game() {
    std::cout << "entro a estadisticas \n";

    QWidget* info_ranking = new QWidget();
    info_ranking->setStyleSheet("QWidget { background-color: rgb(36, 36, 36); color: rgb(255, 255, "
                                "255); font-size: 14px;}");
    info_ranking->setWindowTitle("Scores");

    std::map<player_id_t, InfoPlayer> cts;
    std::map<player_id_t, InfoPlayer> tts;
    filter_table(cts,tts);

    info_ranking->resize(900, 500);
    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(add_table(cts,"Rankig Counter-Terrorist"),0,0);
    mainLayout->addWidget(add_table(tts,"Ranking Terrorist"),0,1);
    mainLayout->addWidget(graficoBarrasEquipo("CT", info_ranking), 2, 0);
    mainLayout->addWidget(graficoBarrasEquipo("TT", info_ranking), 2, 1);
    info_ranking->show();
    return 0;
}

ScoreBoard::~ScoreBoard() {}
