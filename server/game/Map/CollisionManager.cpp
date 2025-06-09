#include "CollisionManager.h"
#define Wall '#'
#define Floor ' '
#include <iostream>

bool CollisionManager::check_movement(player_id_t id, const Position& next_position) {
    auto it = players_in_map.find(id);
    if (it == players_in_map.end())
        return false;
    Position destino = it->second.position + next_position;
    // Aca los destinos son distintos porque la matriz esta "invertida" con respecto a los vectores
    int x = destino.x;
    int y = destino.y;
    if (!is_a_wall(x, y)) {
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
        std::shared_ptr<IInteractuable> casted_bomb = bomb.second;
        player.player.lock()->equip(casted_bomb);
        bomb.second->set_equiped();
    }
}
void CollisionManager::check_weapon_stepped(PlayerEntity& player) {
    auto it = dropped_things.find(player.position);
    if (it == dropped_things.end())
        return;
    if (player.player.lock() && player.player.lock()->equip(it->second))
        dropped_things.erase(it);
}
void CollisionManager::add_bullet_image(const Vector2f& initial_pos, const Vector2f& final_pos) {
    coordinate_t x_initial = static_cast<coordinate_t>(std::round(initial_pos.x));
    coordinate_t y_initial = static_cast<coordinate_t>(std::round(initial_pos.y));
    coordinate_t x_final = static_cast<coordinate_t>(std::round(final_pos.x));
    coordinate_t y_final = static_cast<coordinate_t>(std::round(final_pos.y));
    Position initial_cast(x_initial, y_initial);
    Position end_cast(x_final, y_final);
    BulletImage image(initial_cast, end_cast);
    bullets_image.push_back(std::move(image));
}
bool CollisionManager::is_a_wall(coordinate_t x, coordinate_t y) {
    return x < walls.size() && y < walls[0].size() && walls[x][y] == Wall;
}

bool CollisionManager::check_bullet_wall(const Vector2f& initial_pos, const Vector2f& final_pos) {
    Vector2f direction(initial_pos.x - final_pos.x, initial_pos.y - final_pos.y);
    direction.x = (direction.x > 0) ? 1 : -1;
    direction.y = (direction.y > 0) ? 1 : -1;
    float distance = initial_pos.distance(final_pos);
    float step = 0.5;
    float traveled = 0;
    Vector2f current_pos = initial_pos;
    while (traveled <= distance) {
        coordinate_t x = static_cast<coordinate_t>(std::round(current_pos.x));
        coordinate_t y = static_cast<coordinate_t>(std::round(current_pos.y));
        if (x < walls.size() && y < walls[0].size()) {
            return false;
        }
        if (is_a_wall(x, y)) {
            add_bullet_image(initial_pos, current_pos);
            return true;
        }
        current_pos.x += current_pos.x * step * direction.x;
        current_pos.y += current_pos.y * step * direction.y;
        traveled += step;
    }
    return false;
}
std::vector<BulletImage> CollisionManager::get_bullets_image() { return bullets_image; }
void CollisionManager::check_damage_players(player_id_t caster, ColliderDamage& collider_damage,
                                            std::vector<PlayerEntity>& players_affected) {
    for (auto& player: players_in_map) {
        if (player.first == caster)
            continue;
        if (!collider_damage.collider->is_in(player.second.position))
            continue;
        players_affected.push_back(player.second);
    }
}
void CollisionManager::check_damage_collider(player_id_t caster, ColliderDamage& collider_damage) {
    bullets_image.clear();
    std::vector<PlayerEntity> players_affected;
    PlayerEntity player_caster = players_in_map[caster];
    Vector2f pos_caster(player_caster.position.x, player_caster.position.y);
    Vector2f end = collider_damage.collider->get_end();
    if (check_bullet_wall(pos_caster, end))
        return;
    check_damage_players(caster, collider_damage, players_affected);
    if (players_affected.empty()) {
        add_bullet_image(pos_caster, end);
        return;
    }
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
            pos_nearest = new_pos;
            nearest = player;
        }
    }
    if (nearest.player.lock()) {
        uint8_t damage = collider_damage.damage_calculator(min_distance);
        nearest.player.lock()->damage(damage);
        if (nearest.player.lock()->is_dead())
            player_caster.player.lock()->get_points();
        add_bullet_image(pos_caster, pos_nearest);
    }
}

void CollisionManager::check_damage() {
    check_damage_collider(damage_collider.first, damage_collider.second);
}

void CollisionManager::drop(Position& player_position, std::shared_ptr<IInteractuable>& dropable) {
    this->dropped_things.insert(std::make_pair(player_position, std::move(dropable)));
}
void CollisionManager::add_damage_collider(player_id_t id, ColliderDamage& collider_damage) {
    damage_collider = std::make_pair(id, std::move(collider_damage));
}
std::vector<WeaponDropped> CollisionManager::get_dropped_things_images() {
    std::vector<WeaponDropped> weapon_images;
    std::transform(dropped_things.begin(), dropped_things.end(), back_inserter(weapon_images),
                   [](const auto& weapon) {
                       return WeaponDropped(weapon.second->get_weapon_code(), weapon.first);
                   });
    return weapon_images;
}
// Llamad pidiendo las balas, => clear
