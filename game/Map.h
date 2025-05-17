#ifndef MAP_H_
#define MAP_H_
//  "Copyright 2025 Yaco Santamarina"
#include <memory>
#include <string>
#include <vector>

#include "Bullet.h"
#include "Physics.h"
#include "Weapon.h"
class Map {
    std::string map_name;
    // std::vector<Wall> walls;
    // Rectangle bomb_A;
    // Rectangle bomb_B;
    // Rectangle spawn_CT;
    // Rectangle spawn_TT;

    std::vector<std::unique_ptr<Weapon>> dropped_weapons;
    std::vector<Bullet> bullets_in_air;

    void check_collisions();
    void handle_collisions();

public:
    explicit Map(const std::string& _map_name): map_name(_map_name) {}
    void update_map_state();
};
#endif  // MAP_H_
