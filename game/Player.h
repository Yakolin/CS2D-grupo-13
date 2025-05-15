#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

// #include "Equipement.h"
#include <string>
#include <utility>

#include "Physics.h"
#include "Type.h"

class Player {
public:
    Player(int _id, std::string&& _nick_name, Vector2&& _position):
            id(_id),
            nick_name(std::move(_nick_name)),
            position(std::move(_position)),
            health(100),
            points(0) {}

    void move(Vector2&& new_position);
    /*
    void get_damage(int damage);
    void change_weapon_equiped();
    void fire_weapon_equiped();
    */
private:
    int id;
    std::string nick_name;
    Vector2 position;
    // Equiment equipement;
    int health;
    int points;
};

#endif  // GAME_PLAYER_H_
