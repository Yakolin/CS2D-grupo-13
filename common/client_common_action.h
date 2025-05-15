#ifndef CLIENT_COMMON_ACTION_H
#define CLIENT_COMMON_ACTION_H

#include <string>

#include "lobby_types.h"

class CreateGameCommon {
protected:
    const std::string game_name;

public:
    CreateGameCommon(const std::string& game_name): game_name(game_name) {}
    virtual ~CreateGameCommon();
};

class JoinGameCommon {
protected:
    const std::string game_name;

public:
    JoinGameCommon(const std::string& game_name): game_name(game_name) {}
    virtual ~JoinGameCommon();
};

class ListGamesCommon {
public:
    ListGamesCommon() = default;
    virtual ~ListGamesCommon();
};

#endif  // !CLIENT_COMMON_ACTION_H