#include "CollisionManager.h"

#include <iostream>

bool CollisionManager::check_movement(player_id_t id, const Position& next_position) {
    auto it = players_in_map.find(id);
    if (it == players_in_map.end())
        return false;
    Position destino = it->second.position + next_position;
    // Aca los destinos son distintos porque la matriz esta "invertida" con respecto a los vectores
    if (!is_a_collision(destino) && !player_in(destino)) {
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
    if (player.player.lock() && player.player.lock()->equip(it->second)) {
        dropped_things.erase(it);
    }
}

void CollisionManager::add_bullet_image(const Vector2f& initial_pos, const Vector2f& final_pos,
                                        const ColliderDamage& collider_info) {
    coordinate_t x_initial = static_cast<coordinate_t>(std::round(initial_pos.x));
    coordinate_t y_initial = static_cast<coordinate_t>(std::round(initial_pos.y));
    coordinate_t x_final = static_cast<coordinate_t>(std::round(final_pos.x));
    coordinate_t y_final = static_cast<coordinate_t>(std::round(final_pos.y));
    Position initial_cast(x_initial, y_initial);
    Position end_cast(x_final, y_final);
    BulletImage image(initial_cast, end_cast, collider_info.width, collider_info.code);
    bullets_image.push_back(std::move(image));
}

bool CollisionManager::is_a_collision(const Position& pos) {
    return std::find(collision_pos.begin(), collision_pos.end(), pos) != collision_pos.end();
}
bool CollisionManager::player_in(const Position& pos) {
    for (const auto& player: players_in_map)
        if (player.second.position == pos && !player.second.player.lock()->is_dead())
            return true;
    return false;
}
bool CollisionManager::check_bullet_wall(const Vector2f& initial_pos, const Vector2f& final_pos,
                                         const ColliderDamage& collider_info) {
    Vector2f direction(final_pos.x - initial_pos.x, final_pos.y - initial_pos.y);
    direction.normalize();
    float distance = initial_pos.distance(final_pos);
    float step = 0.2;
    float traveled = 0;
    Vector2f current_pos = initial_pos;
    while (traveled <= distance) {
        coordinate_t x = static_cast<coordinate_t>(std::round(current_pos.x));
        coordinate_t y = static_cast<coordinate_t>(std::round(current_pos.y));
        if (is_a_collision(Position(x, y))) {
            add_bullet_image(initial_pos, current_pos, collider_info);
            return true;
        }
        current_pos.x += step * direction.x;
        current_pos.y += step * direction.y;
        traveled += step;
    }
    // Aca podriamos hacer ruidos de chocar con paredes
    return false;
}

std::vector<BulletImage> CollisionManager::get_bullets_image() {
    std::vector<BulletImage> bullets_image_aux = std::move(this->bullets_image);
    this->bullets_image.clear();
    this->damages_collider.clear();
    return bullets_image_aux;
}

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
    std::vector<PlayerEntity> players_affected;
    PlayerEntity player_caster = players_in_map[caster];
    Vector2f end = collider_damage.collider->get_end();
    Vector2f origin = collider_damage.collider->get_start();
    std::shared_ptr<Sound> sound = std::make_shared<SoundShoot>(collider_damage.code);
    sound_manager.emit_sound(sound, player_caster.position);
    check_damage_players(caster, collider_damage, players_affected);
    if (players_affected.empty()) {
        // Si no se detecto ningun jugador, revisamos si hay un muro entre medio
        if (check_bullet_wall(origin, end, collider_damage))
            return;
        // En caso de que no, directamente la linea es toda su distancia inicial
        add_bullet_image(origin, end, collider_damage);
        return;
    }
    PlayerEntity nearest = players_affected[0];
    Vector2f pos_nearest(nearest.position.x, nearest.position.y);
    float min_distance = origin.distance(pos_nearest);
    for (auto& player: players_affected) {
        if (!player.player.lock())
            continue;
        Vector2f new_pos(player.position.x, player.position.y);
        float aux = origin.distance(new_pos);
        if (aux < min_distance) {
            min_distance = aux;
            pos_nearest = new_pos;
            nearest = player;
        }
    }
    // Aca buscamos de todos los detectados, que son a lo sumo 10, el mas cercano
    // Ya detectado el mas cercano, revisamos si hay un muro entre medio
    if (check_bullet_wall(origin, pos_nearest, collider_damage))
        return;
    if (nearest.player.lock()) {
        std::cout << "Se detecto un enemigo golpeado\n";
        uint8_t damage = collider_damage.damage_calculator(min_distance);
        std::random_device rd;
        std::mt19937 rand(rd());
        // Esto hay q hacerlo x yaml
        std::uniform_int_distribution<uint8_t> dist(0, 4);
        int random_num = dist(rand);
        if (!nearest.player.lock()->is_dead()) {
            if (random_num != 0) {
                nearest.player.lock()->damage(damage);
            }
            if (nearest.player.lock()->is_dead()) {
                std::cout << "Se murio el otro jugador, felicidades :)\n";
                player_caster.player.lock()->get_points();
            }
        }
        add_bullet_image(origin, end, collider_damage);
    }
}

void CollisionManager::check_damage() {
    for (auto& collider: damages_collider) check_damage_collider(collider.first, collider.second);
}

void CollisionManager::drop(Position& player_position, std::shared_ptr<IInteractuable>& dropable) {
    this->dropped_things.insert(std::make_pair(player_position, std::move(dropable)));
}
void CollisionManager::add_damage_collider(player_id_t id, ColliderDamage& collider_damage) {
    damages_collider.push_back(std::make_pair(id, std::move(collider_damage)));
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
