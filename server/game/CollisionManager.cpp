#include "CollisionManager.h"

#include <iostream>

bool CollisionManager::check_movement(player_id_t id, const Position& next_position) {
    auto it = players_in_map.find(id);
    if (it == players_in_map.end())
        return false;
    Position destino = it->second.position + next_position;
    // Aca los destinos son distintos porque la matriz esta "invertida" con respecto a los vectores
    int x = destino.x;
    int y = destino.y;
    if (walls[y][x] != Wall) {
        it->second.position += next_position;
        if (it->second.player.lock()->get_team() == Team::TT)
            check_bomb_stepped(it->second);
        check_weapon_stepped(it->second);
    }
    return true;
}
void CollisionManager::check_bomb_stepped(PlayerEntity& player) {
    if (!(player.position == bomb.first))
        return;
    if (player.player.lock() && !bomb.second->is_activate()) {
        std::shared_ptr<IDroppable> casted_bomb = bomb.second;
        player.player.lock()->equip(casted_bomb);
        bomb.second->set_equiped();
        std::cout << "Bomba equipada\n";
    } else {
        std::cout << "La bomba esta activada, perdon\n";
    }
}
void CollisionManager::check_weapon_stepped(PlayerEntity& player) {
    auto it = dropped_things.find(player.position);
    if (it == dropped_things.end())
        return;
    if (player.player.lock() && player.player.lock()->equip(it->second))
        dropped_things.erase(it);
}
void CollisionManager::check_damage_collider(player_id_t caster, ColliderDamage& collider_damage) {
    std::vector<PlayerEntity> players_affected;
    PlayerEntity player_caster = players_in_map[caster];
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
    Vector2f pos_caster(player_caster.position.x, player_caster.position.y);
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
    if (nearest.player.lock()) {
        uint8_t damage = collider_damage.damage_calculator(min_distance);
        nearest.player.lock()->damage(damage);
        if (nearest.player.lock()->is_dead())
            player_caster.player.lock()->get_points(damage);
    }
}

void CollisionManager::check_damage() {
    // A lo sumo hay 10 colliders creo, no deberia haber problema con complejidad)?
    for (auto& collider: damage_colliders) check_damage_collider(collider.first, collider.second);
    damage_colliders.clear();
}

void CollisionManager::drop(Position& player_position, std::shared_ptr<IDroppable>& dropable) {
    this->dropped_things.insert(std::make_pair(player_position, std::move(dropable)));
}
void CollisionManager::add_damage_collider(player_id_t id, ColliderDamage& collider_damage) {
    damage_colliders.insert(std::make_pair(id, std::move(collider_damage)));
}
std::vector<WeaponDropped> CollisionManager::get_dropped_things_images() {
    std::vector<WeaponDropped> weapon_images;
    std::transform(dropped_things.begin(), dropped_things.end(), back_inserter(weapon_images),
                   [](const auto& weapon) {
                       return WeaponDropped(weapon.second->get_weapon_code(), weapon.first);
                   });
    return weapon_images;
}
