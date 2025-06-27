#ifndef LOBBY_ACTION_H
#define LOBBY_ACTION_H

#include <string>
#include <vector>
enum class LobbyAction { CREATE, JOIN, LIST };
#include "game_info.h"

/*
    LOBBY ACTIONS
*/

class CreateGame {
public:
    std::string game_name;
    MapName map_name;
    Skins skins;
    explicit CreateGame(std::string& game_name, MapName map_name, Skins skins):
            game_name(game_name), map_name(map_name), skins(skins) {}
    ~CreateGame() = default;
};

class JoinGame {
public:
    std::string game_name;
    Skins skins;
    explicit JoinGame(std::string& game_name, Skins skins): game_name(game_name), skins(skins) {}
    ~JoinGame() = default;
};

class ListGame {
public:
    std::vector<std::string> list_games;
    explicit ListGame(const std::vector<std::string>& list_games): list_games(list_games) {}
    ~ListGame() {}
};


#endif  // !LOBBY_ACTION_H
