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
#include "PlayerType.h"
#include "Weapon.h"

class Map {
private:
    std::map<player_id_t, std::shared_ptr<Player>>& players;  // pid - vector2
    std::string map_name;
    // std::vector<Wall> walls;
    // Rectangle spawn_CT;
    // Rectangle spawn_TT;
    std::vector<std::unique_ptr<Weapon>> dropped_weapons;
    std::vector<Bullet> bullets_in_air;
    std::unique_ptr<Bomb> bomb;

    /* Collisions */
    void check_bullets_collisions();
    void check_collisions();
    void update_bullets_in_air();

public:
    Rectangle bomb_A;
    Rectangle bomb_B;
    explicit Map(const std::string& _map_name,
                 std::map<player_id_t, std::shared_ptr<Player>>& players):
            players(players),
            map_name(_map_name),
            bomb_A(1, 1, Vector2(6, 6)),
            bomb_B(1, 1, Vector2(7, 8)) {}

    void update_map_state();
    void add_bullet(Bullet& bullet) { bullets_in_air.push_back(std::move(bullet)); }
    void add_weapon(std::unique_ptr<Weapon>& weapon) {
        dropped_weapons.push_back(std::move(weapon));
    }
    void add_bomb(std::unique_ptr<Bomb>& _bomb) { bomb = std::move(_bomb); }
};
#endif  // MAP_H_
