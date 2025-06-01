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
void Map::respawn_players(const std::map<player_id_t, Team>& players_teams) {
    std::cout << "Respawning players\n";
    for (const auto& player: players_teams) {
        auto it = players_in_map.find(player.first);
        if (it != players_in_map.end()) {
            if (player.second == Team::CT) {
                it->second.position = spawn_CT.get_random_position();
            } else {
                it->second.position = spawn_TT.get_random_position();
            }
        } else {
            throw MapException("Can´t found players in the map to respawn");
        }
    }
}

void Map::add_player(player_id_t id, std::weak_ptr<ICanInteract> player) {
    players_in_map.insert(std::make_pair(id, PlayerEntity{player, Position(5, 5)}));
}
void Map::charge_zone(Rectangle& zone, const Position& position) {
    zone = Rectangle(WidthSpawn, HeightSpawn, position);
}

//Charge map debe recibir el tipo o en todo caso el path del mapa, que game manager se encargue de eso.
void Map::charge_map(const std::string& map_name) {
    std::ifstream path(map_name);
    if (!path.is_open()) {
        throw MapException("Can´t open the file of the game " + map_name);
    }
    std::string line;
    bool spawn_tt = false, spawn_ct = false;
    while (getline(path, line)) {
        std::vector<char> fila;
        for (size_t i = 0; i < line.size(); i++) {
            char c = line[i];
            if (c == 'C') {
                Position pos(i, walls.size());
                charge_zone(spawn_CT, pos);
                spawn_ct = true;
                c = ' ';
            } else if (c == 'T') {
                Position pos(i, walls.size());
                charge_zone(spawn_TT, pos);
                spawn_tt = true;
                c = ' ';
            }
            fila.push_back(c);
        }
        walls.push_back(fila);
    }
    if (!spawn_ct or !spawn_tt)
        throw MapException("The map doesn´t have all the zones of Spawns and Plant");
}

void Map::move(player_id_t id, const Position& direction) {
    auto it = players_in_map.find(id);
    if (it != players_in_map.end()) {
        if (auto p = it->second.player.lock()) {
            if (collision_manager.valid_movement(it->second.position, direction))
                it->second.position += direction;
            return;
        }
    }
    throw MapException("Can´t found players in the map to move");
}

void Map::spawn_collider(player_id_t id_spawn, damage_collider_t& wanted) {
    Position aux = get_position(id_spawn);
    Vector2f player_pos(aux.x, aux.y);
    float dir_x = wanted.mouse_position.x - player_pos.x;
    float dir_y = wanted.mouse_position.y - player_pos.y;
    Vector2f relative_direction(dir_x, dir_y);
    relative_direction.normalize();
    relative_direction.x *= wanted.distance;
    relative_direction.y *= wanted.distance;
    std::unique_ptr<Collider> line = std::make_unique<Line>(
            std::move(player_pos), std::move(relative_direction), wanted.width);
    damage_colliders.insert(std::make_pair(id_spawn, std::move(line)));
}
