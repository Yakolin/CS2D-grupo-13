#include "Map.h"

#include <algorithm>

void Map::check_bullets_collisions() {
    /*
    for (auto bullet = bullets_in_air.begin(); bullet != bullets_in_air.end(); bullet++) {
        auto player_afected =
                std::find_if(players_positions.begin(), players_positions.end(), [&](const auto&
    player_pair) { return (player_pair.second->get_id() != bullet->id) && (bullet->position -
    player_pair.second->position).get_norm() <= bullet->size;
                });
        if (player_afected != players_positions.end()) {
            player_afected->second->get_damage(bullet->damage);
            bullets_in_air.erase(bullet);
            break;
        }
    }
    */
}
void Map::check_collisions() {
    check_bullets_collisions();  // REVISAR LA COLISION DE LAS BALAS ya que Vector2 es con uint16
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
void Map::move_player(player_id_t id, const Vector2& direction) {
    // Chekear con el colliderManager si esta posicion es valida
    auto it = players_positions.find(id);
    if (it != players_positions.end()) {
        it->second += direction;
    }
    // Exception?
}
Vector2 Map::get_position(player_id_t id) {
    auto it = players_positions.find(id);
    if (it != players_positions.end())
        return it->second;
    return Vector2(0, 0);
    // Exception?
}
