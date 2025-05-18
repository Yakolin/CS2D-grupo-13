#ifndef MAP_H_
#define MAP_H_
//  "Copyright 2025 Yaco Santamarina"
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Bullet.h"
#include "Physics.h"
#include "Player.h"
#include "PlayersTypes.h"
#include "Weapon.h"

class Map {
private:
    enum CollisionType {
        BULLET_WALL,
        BULLET_WEAPON,
        BULLET_PLAYER,
        BULLET_BOMB_A,
        BULLET_BOMB_B,
        PLAYER_WEAPON,
        PLAYER_BOMB_A,
        PLAYER_BOMB_B
    };
    std::map<player_id_t, std::shared_ptr<Player>>& players;
    std::string map_name;
    // std::vector<Wall> walls;
    // Rectangle bomb_A;
    // Rectangle bomb_B;
    // Rectangle spawn_CT;
    // Rectangle spawn_TT;
    std::vector<std::unique_ptr<Weapon>> dropped_weapons;
    std::vector<Bullet> bullets_in_air;


    /* Collisions */
    void check_bullets_collisions();
    void check_collisions();
    void update_bullets_in_air();

public:
    explicit Map(const std::string& _map_name,
                 std::map<player_id_t, std::shared_ptr<Player>>& players):
            players(players), map_name(_map_name) {}
    void update_map_state();
    void add_bullet(Bullet& bullet) { bullets_in_air.push_back(std::move(bullet)); }
    void add_weapon(std::unique_ptr<Weapon>& weapon) {
        dropped_weapons.push_back(std::move(weapon));
    }
};
#endif  // MAP_H_
