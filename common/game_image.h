#ifndef GAME_IMAGE_H
#define GAME_IMAGE_H

#include <cstdint>
#include <vector>

#include "player_command_types.h"
#include "utility.h"

using length_players_images_t = std::uint16_t;


class PlayerImage {
public:
    player_id_t player_id;
    Position position;
    int health;
    int points;
    // Aca falta manejar las armas
    PlayerImage(player_id_t player_id, Position position, int health, int points):
            player_id(player_id), position(position), health(health), points(points) {}
    ~PlayerImage() = default;
};

class GameImage {
public:
    GameImage() = default;
    ~GameImage() = default;
    std::vector<PlayerImage> players_images;
    // Balas en el aire
    // Bomba
    // Drops
    // Sonidos)?
};

#endif  // !GAME_IMAGE_H