#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_
#include <algorithm>
#include <map>
#include <memory>
#include <vector>

#include "../../common/utility.h"

#include "Colliders.h"

class CollisionManager {
    std::map<player_id_t, Position>& players;
    std::map<player_id_t, std::unique_ptr<Collider>>& damage_colliders;
    // std::vector<Dropped> dropped
public:
    explicit CollisionManager(std::map<player_id_t, Position>& players_map,
                              std::map<player_id_t, std::unique_ptr<Collider>>& damage_colliders):
            players(players_map), damage_colliders(damage_colliders) {}
};

#endif  // COLLISION_MANAGER_H_
