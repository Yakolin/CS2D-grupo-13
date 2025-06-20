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
#include "../Sounds/SoundManager.h"
#include "../Weapons/SpecialWeapons.h"
#include "../Weapons/Weapon.h"

#include "CollisionManager.h"
#include "IDroppableZone.h"
#include "IGameZone.h"
#include "ISpawneableZone.h"
#include "MapConfig.h"
#include "MapExeption.h"
class Map: public IGameZone, public ISpawneableZone, public IDroppableZone {
private:
    MapName map_name;
    MapConfig map_config;
    std::vector<Position> collision_pos;  // Vector de posiciones chocables
    Rectangle spawn_CT, spawn_TT, bomb_A, bomb_B;
    std::pair<Position, std::shared_ptr<Bomb>> bomb;
    SoundManager& sound_manager;
    CollisionManager collision_manager;
    std::map<player_id_t, player_entity_t> players_in_map;
    void charge_map();
    Position get_random_position();

public:
    explicit Map(const MapName& _map_name, std::shared_ptr<Bomb> bomb_ptr,
                 SoundManager& sound_manager):
            IGameZone(),
            ISpawneableZone(),
            IDroppableZone(),
            map_name(_map_name),
            map_config(map_name),
            bomb(std::make_pair(Position(10, 10), bomb_ptr)),
            sound_manager(sound_manager),
            collision_manager(collision_pos, players_in_map, bomb, sound_manager) {
        charge_map();
    }
    void update_map_state();
    Position get_position(player_id_t player_id);
    void add_player(player_id_t id, std::weak_ptr<ICanInteract> player);
    void remove_player(player_id_t id);
    void update_teams(const std::map<player_id_t, Team>& players_teams);
    void respawn_players();
    MapInfo get_map_info();
    std::vector<BulletImage> get_bullets_in_air();
    std::vector<WeaponDropped> get_dropped_things_images() {
        return collision_manager.get_dropped_things_images();
    }
    BombImage get_bomb_image() { return BombImage(bomb.first, bomb.second->get_state()); }
    virtual void defuse_bomb(const player_id_t& player_id) override;
    void move(player_id_t id, const Position& direction) override;
    void spawn_random_weapons(const std::vector<std::shared_ptr<IInteractuable>>& weapons);
    void spawn_collider(player_id_t id_spawn, collider_solicitude_t& wanted) override;
    void drop(const player_id_t& player_id, std::shared_ptr<IInteractuable>& droppable) override;
    virtual bool plant_bomb(const player_id_t& id_spawn) override;
};

#endif  // MAP_H_
