#ifndef MAP_H_
#define MAP_H_
//  "Copyright 2025 Yaco Santamarina"
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../common/game_image.h"

#include "CollisionManager.h"
#include "IDropeableZone.h"
#include "IGameZone.h"
#include "ISpawneableZone.h"
#include "MapExeption.h"
#include "SpecialWeapons.h"
#include "Weapon.h"

#define WidthSpawn 5
#define HeightSpawn 5

class Map: public IGameZone, public ISpawneableZone, public IDroppableZone {
private:
    std::string map_name;
    std::vector<std::vector<char>> walls;
    Rectangle spawn_CT, spawn_TT, bomb_A, bomb_B;
    CollisionManager collision_manager;
    std::map<player_id_t, player_entity_t> players_in_map;
    std::map<player_id_t, std::unique_ptr<Collider>> damage_colliders;
    bool check_zones(char c, int i);
    void charge_zone(Rectangle& zone, const Position& position);
    void charge_map(const std::string& archivo);

public:
    explicit Map(const std::string& _map_name):
            IGameZone(),
            ISpawneableZone(),
            IDroppableZone(),
            map_name(_map_name),
            collision_manager(walls, players_in_map, damage_colliders) {
        charge_map(map_name);
    }
    void update_map_state();
    Position get_position(player_id_t player_id);
    void add_player(player_id_t id, std::weak_ptr<ICanInteract> player, Team team);
    void update_teams(const std::map<player_id_t, Team>& players_teams);
    void respawn_players();
    void move(player_id_t id, const Position& direction) override;
    void spawn_collider(player_id_t id_spawn, damage_collider_t& wanted) override;
    void drop(const player_id_t& player_id, std::unique_ptr<Weapon>& droppable) override;
};

#endif  // MAP_H_
