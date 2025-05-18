#include "Map.h"

void Map::check_collisions() {
    for (Bullet bullet: bullets_in_air) {
        for (auto& player_pair: players) {
            if (bullet.position == player_pair.second->position) {
                player_pair.second->get_damage(bullet.damage);
            }
        }
    }
}
void Map::update_bullets_in_air() {
    for (auto& bullet: bullets_in_air) bullet.move();
}
void Map::update_map_state() {
    update_bullets_in_air();
    check_collisions();
}
