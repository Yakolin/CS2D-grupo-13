#include "Map.h"

#include <algorithm>
#include <iostream>

void Map::update_map_state() {}
void Map::move_player(player_id_t id, const Position& direction) {
    // Chekear con el colliderManager si esta posicion es valida
    auto it = players_positions.find(id);
    if (it != players_positions.end()) {
        it->second += direction;
    }
    // Exception?
}
Position Map::get_position(player_id_t id) {
    auto it = players_positions.find(id);
    if (it != players_positions.end())
        return it->second;
    return Position(0, 0);
    // Exception?
}
void Map::respawn_players(const std::map<player_id_t, Team>& players_teams) {
    for (const auto& player: players_teams) {
        auto it = players_positions.find(player.first);
        if (it != players_positions.end()) {
            if (player.second == Team::CT) {
                it->second = spawn_CT.get_random_position();
            } else {
                it->second = spawn_TT.get_random_position();
            }
        } else {
            // Exception?
        }
    }
}
