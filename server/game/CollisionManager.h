#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_
#include <algorithm>
#include <map>
#include <memory>
#include <vector>

#include "../../common/utility.h"

#include "Colliders.h"
#include "ICanInteract.h"
#define Wall '#'
#define Floor ' '
typedef struct PlayerEntity {
    std::shared_ptr<ICanInteract>& player;
    Position position;
} player_entity_t;

class CollisionManager {
    std::vector<std::vector<char>>& walls;
    std::map<player_id_t, player_entity_t>& players_in_map;
    std::map<player_id_t, std::unique_ptr<Collider>>& damage_colliders;
    // std::vector<Dropped> dropped
public:
    explicit CollisionManager(std::vector<std::vector<char>>& walls,
                              std::map<player_id_t, player_entity_t>& players_in_map,
                              std::map<player_id_t, std::unique_ptr<Collider>>& damage_colliders):
            walls(walls), players_in_map(players_in_map), damage_colliders(damage_colliders) {}
    bool valid_movement(const Position& actual_position, const Position& next_position);
};

#endif  // COLLISION_MANAGER_H_
