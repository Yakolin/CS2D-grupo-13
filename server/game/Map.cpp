#include "Map.h"

#include <algorithm>

void Map::check_bullets_collisions() {
    /*
    for (auto bullet = bullets_in_air.begin(); bullet != bullets_in_air.end(); bullet++) {
        auto player_afected =
                std::find_if(players.begin(), players.end(), [&](const auto& player_pair) {
                    return (player_pair.second->get_id() != bullet->id) &&
                           (bullet->position - player_pair.second->position).get_norm() <=
                                   bullet->size;
                });
        if (player_afected != players.end()) {
            player_afected->second->get_damage(bullet->damage);
            bullets_in_air.erase(bullet);
            break;
        }
    }
    */
}
void Map::check_collisions() {
    check_bullets_collisions(); // REVISAR LA COLISION DE LAS BALAS ya que Vector2 es con uint16
    // Check collision walls
    // Check dropped weapons
}
void Map::update_bullets_in_air() {
    for (auto& bullet: bullets_in_air) bullet.move();
}
void Map::update_map_state() {
    update_bullets_in_air();
    check_collisions();
}
