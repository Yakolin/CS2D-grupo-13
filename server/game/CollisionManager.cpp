#include "CollisionManager.h"

#include <iostream>

bool CollisionManager::valid_movement(const Position& actual_position,
                                      const Position& next_position) {
    Position destino = actual_position + next_position;
    // Aca los destinos son distintos porque la matriz esta "invertida" con respecto a los vectores
    int x = destino.x;
    int y = destino.y;
    return walls[y][x] != Wall;
}
void CollisionManager::check_damage_collider(player_id_t caster,
                                             const std::unique_ptr<Collider>& collider) {
    std::vector<PlayerEntity> players_affected;
    // A lo sumo 10 players, no es algo costoso
    for (auto& player: players_in_map) {
        if (player.first == caster)
            continue;
        if (!collider->is_in(player.second.position))
            continue;
        players_affected.push_back(player.second);
    }
    if (players_affected.empty())
        return;
    Vector2f pos_caster(players_in_map[caster].position.x, players_in_map[caster].position.y);
    PlayerEntity nearest = players_affected[0];
    Vector2f pos_nearest(nearest.position.x, nearest.position.y);
    float min_distance = pos_caster.distance(pos_nearest);
    for (auto& player: players_affected) {
        if (!player.player.lock())
            continue;
        Vector2f new_pos(player.position.x, player.position.y);
        float aux = pos_caster.distance(new_pos);
        if (aux < min_distance) {
            min_distance = aux;
            nearest = player;
        }
    }
    if (!nearest.player.lock())
        return;
    nearest.player.lock()->damage(5);  // Esto en realidad debe de calcularlo una funcion
}
void CollisionManager::check_damage() {
    // A lo sumo hay 10 colliders creo, no deberia haber problema con complejidad)?
    for (const auto& collider: damage_colliders)
        check_damage_collider(collider.first, collider.second);
    damage_colliders.clear();
}
