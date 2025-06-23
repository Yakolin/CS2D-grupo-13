#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <QBarSet>
#include <QTableWidget>
#include <QVBoxLayout>
#include <map>
#include <string>

#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QValueAxis>

#include "../tipos.h"

#include "ButtonsCreator.h"


using namespace QtCharts;

class ScoreBoard {
public:
    explicit ScoreBoard(const std::map<player_id_t, InfoPlayer>& table);

    int show_scores_game();

    ~ScoreBoard();

private:
    std::map<player_id_t, InfoPlayer> scores;

    void filter_table(std::map<player_id_t, InfoPlayer>& cts,
                      std::map<player_id_t, InfoPlayer>& tts);

    /*
    pre: recibe un mapa cargado con los puntajes de los jugadores y un QVBoxLayout
    post: crea una tabla con los puntajes de los jugadores y lo apila en el QVBoxLayout
    */
    QWidget* add_table(std::map<player_id_t, InfoPlayer>& score_table, const QString& title);

    QChartView* graficoBarrasEquipo(const std::string& equipo, QWidget* parent);

    void staly_chart(QChart* chart, QBarCategoryAxis* axisX, QValueAxis* axisY);

    void style(QTableWidget* table);
};

#endif  // SCOREBOARD_H
