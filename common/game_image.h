#ifndef GAME_IMAGE_H
#define GAME_IMAGE_H

#include <cstdint>
#include <vector>

#include "game_image.h"
#include "player_command_types.h"


using length_players_images_t = std::uint16_t;
using coordinate_t = std::uint16_t;

class Position {  // Esto puede ser directamente un Vector2
public:
    coordinate_t x;
    coordinate_t y;

    Position(coordinate_t x, coordinate_t y): x(x), y(y) {}
    ~Position() = default;
    bool operator==(const Position& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Position& other) const { return !(*this == other); }
};

class PlayerImage {
public:
    player_id_t player_id;
    Position position;
    // int health;
    // int points;
    //  Aca falta manejar las armas
    PlayerImage(player_id_t player_id, Position position):
            player_id(player_id), position(position) {}
    // PlayerImage(player_id_t player_id, Position position, int health, int points):
    // player_id(player_id), position(position), health(health), points(points) {}
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