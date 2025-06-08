#ifndef MAP_H_
#define MAP_H_
//  "Copyright 2025 Yaco Santamarina"
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../../common/game_image.h"
#include "../../../common/game_info.h"
#include "../Weapons/SpecialWeapons.h"
#include "../Weapons/Weapon.h"

#include "CollisionManager.h"
#include "IDroppableZone.h"
#include "IGameZone.h"
#include "ISpawneableZone.h"
#include "MapExeption.h"

#define WidthSpawn 5
#define HeightSpawn 5

class Map: public IGameZone, public ISpawneableZone, public IDroppableZone {
private:
    MapName map_name;
    std::vector<std::vector<char>> walls;
    Rectangle spawn_CT, spawn_TT, bomb_A, bomb_B;
    std::pair<Position, std::shared_ptr<Bomb>> bomb;
    CollisionManager collision_manager;
    std::map<player_id_t, player_entity_t> players_in_map;
    bool check_zones(char c, int i);
    void charge_zone(Rectangle& zone, const Position& position);
    void charge_map(const MapName& archivo);

public:
    explicit Map(const MapName& _map_name, std::shared_ptr<Bomb> bomb_ptr):
            IGameZone(),
            ISpawneableZone(),
            IDroppableZone(),
            map_name(_map_name),
            bomb(std::make_pair(Position(10, 10), bomb_ptr)),
            collision_manager(walls, players_in_map, bomb) {
        charge_map(map_name);
    }
    void update_map_state();
    Position get_position(player_id_t player_id);
    void add_player(player_id_t id, std::weak_ptr<ICanInteract> player);
    void remove_player(player_id_t id);
    void update_teams(const std::map<player_id_t, Team>& players_teams);
    void respawn_players();
    std::vector<Position> get_walls();
    std::vector<WeaponDropped> get_dropped_things_images() {
        return collision_manager.get_dropped_things_images();
    }
    BombImage get_bomb_image() {
        return BombImage(bomb.first, bomb.second->is_activate(), !bomb.second->is_equiped());
    }

    void move(player_id_t id, const Position& direction) override;
    void spawn_collider(player_id_t id_spawn, collider_solicitude_t& wanted) override;
    void drop(const player_id_t& player_id, std::shared_ptr<IInteractuable>& droppable) override;
    virtual bool plant_bomb(const player_id_t& id_spawn) override;
};

#endif  // MAP_H_
