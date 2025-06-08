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
    std::cout << "Respawning players\n";
    for (auto& player: players_in_map) {
        player.second.position = (player.second.player.lock()->get_team() == Team::CT) ?
                                         spawn_CT.get_random_position() :
                                         spawn_TT.get_random_position();
    }
}
void Map::add_player(player_id_t id, std::weak_ptr<ICanInteract> player) {
    players_in_map.insert(std::make_pair(id, PlayerEntity{player, Position(15, 15)}));
}
void Map::charge_zone(Rectangle& zone, const Position& position) {
    zone = Rectangle(WidthSpawn, HeightSpawn, position);
}

// Charge map debe recibir el tipo o en todo caso el path del mapa, que game manager se encargue de
// eso.
bool Map::check_zones(char c, int i) {
    if (c == 'C') {
        Position pos(i, walls.size());
        charge_zone(spawn_CT, pos);
        return true;
    } else if (c == 'T') {
        Position pos(i, walls.size());
        charge_zone(spawn_TT, pos);
        return true;
    } else if (c == 'A') {
        Position pos(i, walls.size());
        charge_zone(bomb_A, pos);
        return true;
    } else if (c == 'B') {
        Position pos(i, walls.size());
        charge_zone(bomb_B, pos);
        return true;
    }
    return false;
}
void Map::charge_map(const std::string& map_name) {
    if (map_name.empty())
        std::cout << "ola, esto es para evitar flags" << std::endl;
    std::string aux("../../assets/pueblito_azteca.txt");
    std::ifstream path(aux);
    if (!path.is_open()) {
        throw MapException("Can´t open the file of the game " + aux);
    }
    std::string line;
    bool spawn_tt = false, spawn_ct = false, bomb_a, bomb_b;
    while (getline(path, line)) {
        std::vector<char> fila;
        for (size_t i = 0; i < line.size(); i++) {
            char c = line[i];
            bool zone_detected = check_zones(c, i);
            if (zone_detected) {
                if (c == 'C')
                    spawn_ct = true;
                else if (c == 'T')
                    spawn_tt = true;
                else if (c == 'A')
                    bomb_a = true;
                else if (c == 'B')
                    bomb_b = true;
            }
            fila.push_back(c);
        }
        walls.push_back(fila);
    }
    if (!spawn_ct || !spawn_tt || !bomb_a || !bomb_b)
        throw MapException("The map doesn´t have all the zones of Spawns and Plant");
}
std::vector<Position> Map::get_walls() {
    std::vector<Position> walls_pos;
    for (size_t i = 0; i < walls.size(); i++)
        for (size_t j = 0; j < walls[i].size(); j++)
            if (walls[i][j] == Wall)
                walls_pos.push_back(Position(i, j));
    return walls_pos;
}
void Map::move(player_id_t id, const Position& direction) {
    if (collision_manager.check_movement(id, direction))
        return;
    throw MapException("Can´t found players in the map to move");
}

void Map::spawn_collider(player_id_t id_spawn, collider_solicitude_t& wanted) {
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
    collider_damage_t collider_damage = {std::move(line), wanted.damage_function};
    collision_manager.add_damage_collider(id_spawn, collider_damage);
}

void Map::drop(const player_id_t& player_id, std::shared_ptr<IDroppable>& droppable) {
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
    bomb.second->set_on_bomb();
    return true;
}
void Map::remove_player([[maybe_unused]] player_id_t id) {}  // Esto no es asi, acordate de fixearlo
