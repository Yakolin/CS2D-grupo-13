#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_
#include <algorithm>
#include <map>
#include <vector>

#include "Bullet.h"
#include "Physics.h"

class CollisionManager {
    std::map<player_id_t, Vector2>& players;
    std::vector<Bullet>& bullets_in_air;
    // std::vector<Dropped> dropped
public:
    CollisionManager(std::map<player_id_t, Vector2>& players_map, std::vector<Bullet>& bullets):
            players(players_map), bullets_in_air(bullets) {}
};

#endif  // COLLISION_MANAGER_H_
