#ifndef GAME_H
#define GAME_H

#include <string>

class Game
{
private:
    std::string game_name;

public:
    Game(const std::string &game_name);
    ~Game();

    void start_game();
    void stop_game();
};

#endif // !GAME_H
