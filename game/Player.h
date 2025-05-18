#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

// #include "Equipement.h"
#include <string>
#include <utility>

#include "../common/game_image.h"

#include "Equipement.h"
#include "Physics.h"
class Player {
public:
    Vector2 position;
    Player(std::string&& _nick_name, Vector2&& _position):
            nick_name(std::move(_nick_name)),
            position(std::move(_position)),
            health(100),
            points(0) {}

    void move(Vector2&& new_position);
    void fire_weapon_equiped(const Vector2& mouse_pointer);
    void get_damage(float damage);
    virtual PlayerImage get_player_image(player_id_t player_id) = 0;

private:
    std::string nick_name;

protected:  // Por ahora lo dejamo asi
    Equipement equipement;
    int health;
    int points;
};

#endif  // GAME_PLAYER_H_
