#ifndef PLAYER_TYPE_H
#define PLAYER_TYPE_H

#include <string>
#include <utility>

#include "Player.h"
/*
    Tanto los constructores como los destructores puede que cambien
*/
class CounterTerrorist: public Player {
public:
    CounterTerrorist(player_id_t id): Player(id) {}
    ~CounterTerrorist() = default;
    virtual PlayerImage get_player_image(Position& position) override;
};
class Terrorist: public Player {
private:
    // Weapon Bomb
public:
    Terrorist(player_id_t id): Player(id) {}
    ~Terrorist() = default;
    virtual PlayerImage get_player_image(Position& position) override;
    void plant_bomb(Map& map);
};

#endif  // !PLAYER_TYPE_H
