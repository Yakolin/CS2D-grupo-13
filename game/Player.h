#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

// #include "Equipement.h"
#include <string>
#include <utility>
#include <vector>

#include "../common/game_image.h"
#include "../common/player_command_types.h"

#include "Equipement.h"
#include "Map.h"
#include "Physics.h"

class Player {
public:
    Player(player_id_t id, std::string&& _nick_name):
            nick_name(std::move(_nick_name)), id(id), health(100), points(0) {}
    void fire_weapon_equiped(Map& map, Vector2& position, Vector2& direction);
    void get_damage(uint8_t damage);
    virtual PlayerImage get_player_image(Vector2& position) = 0;
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
