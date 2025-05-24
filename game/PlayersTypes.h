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
    CounterTerrorist(player_id_t id, std::string&& _nick_name):
            Player(id, std::move(_nick_name)) {}
    ~CounterTerrorist() = default;
    virtual PlayerImage get_player_image(Vector2& position) override;
};
class Terrorist: public Player {
private:
    // Weapon Bomb
public:
    Terrorist(player_id_t id, std::string&& _nick_name):
            Player(id, std::move(_nick_name)) {}
    ~Terrorist() = default;
    virtual PlayerImage get_player_image(Vector2& position) override;
    void plant_bomb(Map& map);
};

#endif  // !PLAYER_TYPES_H
