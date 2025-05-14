#ifndef MAP_H_
#define MAP_H_
//  "Copyright 2025 Yaco Santamarina"
#include "Physics.h"
#include <string>
class Map {
    std::string map_name;
    // std::vector<Wall> walls;
    // std::vector<Weapon> dropped_weapons;
    // std::vector<Bullet> bullets_in_air;
    public:
    explicit Map(const std::string& _map_name) : map_name(_map_name) {}
    void image_map(){
        
    }
};
#endif // MAP_H_