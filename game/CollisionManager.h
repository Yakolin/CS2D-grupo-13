#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_
#include <algorithm>
#include <map>
#include <vector>

#include "Physics.h"

class CollisionManager {
    std::map<player_id_t, Vector2>& players;
    // std::vector<Dropped> dropped
public:
    explicit CollisionManager(std::map<player_id_t, Vector2>& players_map): players(players_map) {}
};

#endif  // COLLISION_MANAGER_H_
