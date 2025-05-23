#ifndef MAP_H_
#define MAP_H_
//  "Copyright 2025 Yaco Santamarina"
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Colliders.h"
#include "CollisionManager.h"
#include "Specials.h"
#include "Weapon.h"
class Map {
private:
    std::string map_name;
    // std::vector<Wall> walls;
    // Rectangle spawn_CT;
    // Rectangle spawn_TT;
    std::map<player_id_t, Vector2> players_positions;
    std::vector<Weapon> dropped_weapons;
    CollisionManager collision_manager;
    /* Collisions */
    void check_bullets_collisions();
    void check_collisions();

public:
    Rectangle bomb_A;
    Rectangle bomb_B;
    explicit Map(const std::string& _map_name):
            map_name(_map_name),
            collision_manager(players_positions),
            bomb_A(1, 1, Vector2(1, 1)),
            bomb_B(1, 1, Vector2(3202, 3202)) {}
    void update_map_state();
    void move_player(player_id_t id, const Vector2& direction);
    Vector2 get_position(player_id_t player_id);
    void add_player(player_id_t id) {
        players_positions.insert(std::make_pair(id, Vector2(3200, 3200)));
    }
};

#endif  // MAP_H_
