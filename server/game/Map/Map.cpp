#include "Map.h"

#include <algorithm>
#include <iostream>

void Map::update_map_state() { collision_manager.check_damage(); }
Position Map::get_position(player_id_t id) {
    auto it = players_in_map.find(id);
    if (it != players_in_map.end())
        return it->second.position;
    throw MapException("Can´t found player in the map to get the position");
}
void Map::respawn_players() {
    for (auto& player: players_in_map) {
        player.second.position = (player.second.player.lock()->get_team() == Team::CT) ?
                                         spawn_CT.get_random_position() :
                                         spawn_TT.get_random_position();
        while (walls[player.second.position.x][player.second.position.y] == Wall)
            player.second.position = (player.second.player.lock()->get_team() == Team::CT) ?
                                             spawn_CT.get_random_position() :
                                             spawn_TT.get_random_position();
    }
}
void Map::add_player(player_id_t id, std::weak_ptr<ICanInteract> player) {
    players_in_map.insert(std::make_pair(id, PlayerEntity{player, Position(15, 15)}));
}
void Map::charge_map() {
    MapConfig::map_data_t& map_info = map_config.get_map_info();
    this->bomb_A = std::move(map_info.bomb_A);
    this->bomb_B = std::move(map_info.bomb_B);
    this->spawn_TT = std::move(map_info.spawn_TT);
    this->spawn_CT = std::move(map_info.spawn_CT);
    this->walls = std::move(map_info.walls);
    std::vector<Position> walls_pos;
    // Esto tenes que cambiarlo yaco
    for (size_t i = 0; i < walls.size(); i++)
        for (size_t j = 0; j < walls[i].size(); j++)
            if (walls[i][j] == Wall)
                walls_pos.push_back(Position(i, j));
    RectangleInfo bomb_A_info(bomb_A.point_min, bomb_A.point_max);
    RectangleInfo bomb_B_info(bomb_B.point_min, bomb_B.point_max);
    RectangleInfo spawn_TT_info(spawn_TT.point_min, spawn_TT.point_max);
    RectangleInfo spawn_CT_info(spawn_CT.point_min, spawn_CT.point_max);
    map_info_to_client =
            MapInfo(map_name, bomb_A_info, bomb_B_info, spawn_TT_info, spawn_CT_info, walls_pos);
}
MapInfo Map::get_map_info() { return map_info_to_client; }
void Map::move(player_id_t id, const Position& direction) {
    if (collision_manager.check_movement(id, direction))
        return;
    throw MapException("Can´t found players in the map to move");
}

std::vector<BulletImage> Map::get_bullets_in_air() { return collision_manager.get_bullets_image(); }

void Map::spawn_collider(player_id_t id_spawn, collider_solicitude_t& wanted) {
    Position aux = get_position(id_spawn);
    Vector2f player_pos(aux.x, aux.y);
    Vector2f relative_direction(wanted.mouse_position.x - player_pos.x,
                                wanted.mouse_position.y - player_pos.y);
    relative_direction.normalize();
    relative_direction.x *= wanted.distance;
    relative_direction.y *= wanted.distance;
    // Aca le sumo la posicion del jugador, para saber desde donde debe salir la bala
    Vector2f end_pos(relative_direction.x + player_pos.x, relative_direction.y + player_pos.y);
    // Aca es un chekeo para que basicamente no se vayan de rango las balas
    end_pos.x = std::max(0.0f, end_pos.x);
    end_pos.y = std::max(0.0f, end_pos.y);
    std::unique_ptr<Collider> line =
            std::make_unique<Line>(std::move(player_pos), std::move(end_pos), wanted.width);
    collider_damage_t collider_damage = {std::move(line), wanted.damage_function};
    collision_manager.add_damage_collider(id_spawn, collider_damage);
}

void Map::drop(const player_id_t& player_id, std::shared_ptr<IInteractuable>& droppable) {
    Position new_pos = get_position(player_id);
    if (droppable->get_weapon_code() == WeaponCode::BOMB) {
        bomb.second->set_unequiped();
        bomb.first = new_pos;
    } else {
        this->collision_manager.drop(new_pos, droppable);
    }
}
bool Map::plant_bomb(const player_id_t& player_id) {
    Position player_pos = get_position(player_id);
    if (!bomb_A.is_in(player_pos) && !bomb_B.is_in(player_pos))
        return false;
    bomb.first = player_pos;
    return true;
}
void Map::defuse_bomb(const player_id_t& player_id) {
    auto it = players_in_map.find(player_id);
    if (it == players_in_map.end())
        return;
    player_entity_t player_entity = it->second;
    if (!(player_entity.position == bomb.first) ||
        player_entity.player.lock()->get_team() == Team::TT)
        return;
    bomb.second->defuse();
}
Position Map::get_random_position() {
    int x = rand() % walls.size();
    int y = rand() % walls[0].size();
    while (wall[x][y] == Wall) {
        x = rand() % walls.size();
        y = rand() % walls[0].size();
    }
    return Position(x, y);
}
void Map::spawn_random_weapons(const std::vector<std::shared_ptr<IInteractuable>>& weapons) {
    // Esto quiza deberia estar en otro lado, pero en secuencia esta bien y funca
    collision_manager.reset_dropped_things();
    for (std::shared_ptr<IInteractuable> weapon: weapons) {
        Position random_pos = get_random_position();
        collision_manager.drop(random_pos, weapon);
    }
}
void Map::remove_player([[maybe_unused]] player_id_t id) {
    // Esto si seria algo extraño que pase...
    if (players_in_map.find(id) == players_in_map.end())
        throw MapException("Player not found in the map to remove");
    players_in_map.erase(id);
}
