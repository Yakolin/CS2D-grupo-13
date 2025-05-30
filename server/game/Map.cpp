#include "Map.h"

#include <algorithm>
#include <iostream>

void Map::update_map_state() {}
void Map::move(player_id_t id, const Position& direction) {
    auto it = players_in_map.find(id);
    if (it != players_in_map.end()) {
        if (collision_manager.valid_movement(it->second.position, direction))
            it->second.position += direction;
        return;
    }
    throw MapException("Can´t found players in the map to move");
}
Position Map::get_position(player_id_t id) {
    auto it = players_in_map.find(id);
    if (it != players_in_map.end())
        return it->second.position;
    throw MapException("Can´t found player in the map to get the position");
}
void Map::respawn_players(const std::map<player_id_t, Team>& players_teams) {
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

void Map::add_player(player_id_t id, std::shared_ptr<ICanInteract>& player) {
    players_in_map.insert(std::make_pair(id, PlayerEntity{player, Position(5, 5)}));
}
void Map::charge_zone(Rectangle& zone, const Position& position) {
    zone = Rectangle(WidthSpawn, HeightSpawn, position);
}
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
