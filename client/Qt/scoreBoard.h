#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QTableWidget>
#include <QVBoxLayout>
#include <map>
#include <string>

#include "../tipos.h"


class ScoreBoard {
public:
    ScoreBoard();


    /*
    pre: recibe un mapa cargado con los puntajes de los jugadores y un QVBoxLayout
    post: crea una tabla con los puntajes de los jugadores y lo apila en el QVBoxLayout
    */
    void add_table(QVBoxLayout* scores_table);

    void add_ranking(QVBoxLayout* scores_table);
    /*
    pre: recibe un mapa cargado con los puntajes de los jugadores y un ranking de los equipos
    post: muestra los puntajes del juego
    */
    int show_scores_game();

    ~ScoreBoard();

private:
    std::map<std::string, PlayerSummary> scores;
    Rankings ranking_group;
};

#endif  // SCOREBOARD_H
