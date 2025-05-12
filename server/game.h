#ifndef GAME_H
#define GAME_H

#include <string>

class Game
{
private:
    std::string game_name;
    uint16_t number_of_players;

public:
    Game(const std::string &game_name, const uint16_t &number_of_players);
    ~Game() = default;

    void start_game();
    void stop_game();
};

#endif // !GAME_H
