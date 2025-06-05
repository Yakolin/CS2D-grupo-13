#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_
#include <algorithm>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "../../common/utility.h"

#include "Colliders.h"
#include "ICanInteract.h"
#include "SpecialWeapons.h"
#define Wall '#'
#define Floor ' '

typedef struct PlayerEntity {
    std::weak_ptr<ICanInteract> player;
    Position position;
    // Position mouse_position;
    Team team;
} player_entity_t;

typedef struct ColliderDamage {
    std::unique_ptr<Collider> collider;
    std::function<uint8_t(float)> damage_calculator;
} collider_damage_t;

class CollisionManager {
    std::vector<std::vector<char>>& walls;
    std::map<player_id_t, player_entity_t>& players_in_map;
    std::map<player_id_t, ColliderDamage> damage_colliders;
    std::pair<Position, std::shared_ptr<Bomb>>& bomb;
    std::map<std::unique_ptr<Weapon>, Position> dropped_weapons;
    void check_damage_collider(player_id_t caster, ColliderDamage& collider);
    void check_bomb_stepped(PlayerEntity& player);

public:
    explicit CollisionManager(std::vector<std::vector<char>>& walls,
                              std::map<player_id_t, player_entity_t>& players_in_map,
                              std::pair<Position, std::shared_ptr<Bomb>>& bomb):
            walls(walls), players_in_map(players_in_map), bomb(bomb) {}
    bool check_movement(player_id_t id, const Position& next_position);
    void check_damage();
    void drop(const player_id_t& player_id, std::unique_ptr<Weapon>& dropable);
    void add_damage_collider(player_id_t id, ColliderDamage& collider_damage);
};

#endif  // COLLISION_MANAGER_H_
