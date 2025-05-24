#ifndef MAP_H_
#define MAP_H_
//  "Copyright 2025 Yaco Santamarina"
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../common/game_image.h"

#include "CollisionManager.h"
#include "Specials.h"
#include "Weapon.h"

class Map {
private:
    std::string map_name;
    Rectangle spawn_CT;
    Rectangle spawn_TT;
    std::map<player_id_t, Position> players_positions;
    CollisionManager collision_manager;

public:
    std::map<player_id_t, std::unique_ptr<Collider>> damage_colliders;
    explicit Map(const std::string& _map_name):
            map_name(_map_name),
            spawn_CT(5, 5, Position(3100, 3100)),
            spawn_TT(5, 5, Position(3120, 3120)),
            collision_manager(players_positions, damage_colliders) {}
    void update_map_state();
    void move_player(player_id_t id, const Position& direction);
    Position get_position(player_id_t player_id);
    void add_player(player_id_t id) {
        players_positions.insert(std::make_pair(id, Position(3200, 3200)));
    }
    void respawn_players(const std::map<player_id_t, Team>& players_teams);
};

#endif  // MAP_H_
