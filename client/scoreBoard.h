#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QTableWidget>
#include <QVBoxLayout>
#include <map>
#include "tipos.h"


class ScoreBoard  {
public:
    ScoreBoard(QWidget *parent = nullptr);


    void ranking();
    /*
    pre: recibe un mapa cargado con los puntajes de los jugadores y un QVBoxLayout 
    post: crea una tabla con los puntajes de los jugadores y lo apila en el QVBoxLayout
    */
    void add_table(QVBoxLayout *scores_table);

    void add_ranking(QVBoxLayout *scores_table);
    /*
    pre: recibe un mapa cargado con los puntajes de los jugadores y un ranking de los equipos
    post: muestra los puntajes del juego
    */
    int scores_game();
    void setTable(QTableWidget *table);

private:

    std::map<std::string, PlayerSummary> scores;
    Rankings ranking_group;
};

#endif // SCOREBOARD_H