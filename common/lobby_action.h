#ifndef LOBBY_ACTION_H
#define LOBBY_ACTION_H

#include <vector>

enum class LobbyAction { CREATE, JOIN, LIST };

/*
    LOBBY ACTIONS
*/

class CreateGame {
public:
    std::string game_name;
    std::string map_name;
    explicit CreateGame(std::string& game_name, std::string map_name):
            game_name(game_name), map_name(map_name) {}
    ~CreateGame() = default;
};

class JoinGame {
public:
    std::string game_name;
    explicit JoinGame(std::string& game_name): game_name(game_name) {}
    ~JoinGame() = default;
};

class ListGame {
public:
    std::vector<std::string> list_games;
    explicit ListGame(std::vector<std::string> list_games): list_games(list_games) {}
    ~ListGame() {}
};


#endif  // !LOBBY_ACTION_H
