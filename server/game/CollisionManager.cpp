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
void CollisionManager::check_damage_collider(player_id_t caster, ColliderDamage& collider_damage) {
    std::vector<PlayerEntity> players_affected;
    // A lo sumo 10 players, no es algo costoso
    for (auto& player: players_in_map) {
        if (player.first == caster)
            continue;
        if (!collider_damage.collider->is_in(player.second.position))
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
    nearest.player.lock()->damage(collider_damage.damage_calculator(min_distance));
}

void CollisionManager::check_damage() {
    // A lo sumo hay 10 colliders creo, no deberia haber problema con complejidad)?
    for (auto& collider: damage_colliders) check_damage_collider(collider.first, collider.second);
    damage_colliders.clear();
}

void CollisionManager::drop(const player_id_t& player_id, std::unique_ptr<Weapon>& dropable) {
    auto it = this->players_in_map.find(player_id);
    if (it != players_in_map.end()) {
        Position& player_position = it->second.position;
        this->dropped_weapons.insert(std::make_pair(std::move(dropable), player_position));
    }
}
void CollisionManager::add_damage_collider(player_id_t id, ColliderDamage& collider_damage) {
    damage_colliders.insert(std::make_pair(id, std::move(collider_damage)));
}
