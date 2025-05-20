#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

// #include "Equipement.h"
#include <string>
#include <utility>

#include "../common/game_image.h"

#include "Equipement.h"
#include "Physics.h"

class Map;
class Player {
public:
    Vector2 position;
    Player(player_id_t id, std::string&& _nick_name, Vector2&& _position):
            position(std::move(_position)),
            nick_name(std::move(_nick_name)),
            id(id),
            health(100),
            points(0) {}

    void move(Vector2&& new_position);
    void fire_weapon_equiped(Map& map, const Vector2& mouse_pointer);
    void get_damage(uint8_t damage);
    virtual PlayerImage get_player_image() = 0;
    player_id_t get_id() { return id; }

private:
    std::string nick_name;

protected:  // Por ahora lo dejamo asi
    player_id_t id;
    Equipement equipement;
    uint8_t health;
    uint8_t points;
};

#endif  // GAME_PLAYER_H_
