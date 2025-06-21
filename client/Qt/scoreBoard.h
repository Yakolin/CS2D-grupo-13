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
    ScoreBoard();


    /*
    pre: recibe un mapa cargado con los puntajes de los jugadores y un QVBoxLayout
    post: crea una tabla con los puntajes de los jugadores y lo apila en el QVBoxLayout
    */
    void add_table(QGridLayout* scores_table, const int& fil, const int& col);

    void add_filtered_tables(QGridLayout* layout);

    void add_ranking(QGridLayout* scores_table, const int& fil, const int& col);

    QChartView* grafico_pie(QWidget* parent);
    QChartView* graficoBarrasEquipo(const std::string& equipo, QWidget* parent);
    QChartView* graficoBarrasApiladasEquipo(const std::string& equipo, QWidget* parent);
    /*
    pre: recibe un mapa cargado con los puntajes de los jugadores y un ranking de los equipos
    post: muestra los puntajes del juego
    */
    void add_chart(QGridLayout* layout, const int& fil, const int& col);
    int show_scores_game();

    ~ScoreBoard();

private:
    std::map<int, InfoPlayer> scores;
};

#endif  // SCOREBOARD_H
