#ifndef GAME_IMAGE_H
#define GAME_IMAGE_H

#include <cstdint>
#include <vector>

#include "player_command_types.h"

using coordinate_t = std::uint16_t;
using length_players_images_t = std::uint16_t;

class Position {  // esto puede que este a nivel del server tal vez, ya que
                  // seguramente quiera usar Position
public:
    coordinate_t x;
    coordinate_t y;

    Position(coordinate_t x, coordinate_t y): x(x), y(y) {}
    ~Position() = default;
};

class PlayerImage {
public:
    player_id_t player_id;
    Position position;

    PlayerImage(player_id_t player_id, Position position):
            player_id(player_id), position(position) {}
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
