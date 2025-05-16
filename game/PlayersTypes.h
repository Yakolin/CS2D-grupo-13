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
    CounterTerrorist(std::string&& _nick_name, Vector2&& _position):
            Player(std::move(_nick_name), std::move(_position)) {}
    ~CounterTerrorist() = default;
    virtual PlayerImage get_player_image(player_id_t player_id) override;
};
class Terrorist: public Player {
private:
    // Weapon Bomb
public:
    Terrorist(std::string&& _nick_name, Vector2&& _position):
            Player(std::move(_nick_name), std::move(_position)) {}
    ~Terrorist() = default;
    virtual PlayerImage get_player_image(player_id_t player_id) override;
};

#endif  // !PLAYER_TYPES_H
