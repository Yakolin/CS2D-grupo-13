#ifndef PLAYER_TYPES_H
#define PLAYER_TYPES_H

#include <string>
#include <utility>

#include "Player.h"
/*
    Tanto los constructores como los destructores puede que cambien
*/
class CounterTerrorist: public Player {
public:
    CounterTerrorist(int _id, std::string&& _nick_name, Vector2&& _position):
            Player(_id, std::move(_nick_name), std::move(_position)) {}
    ~CounterTerrorist() = default;
};
class Terrorist: public Player {
public:
    Terrorist(int _id, std::string&& _nick_name, Vector2&& _position):
            Player(_id, std::move(_nick_name), std::move(_position)) {}
    ~Terrorist() = default;
};

#endif  // !PLAYER_TYPES_H
