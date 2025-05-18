#ifndef GAME_IMAGE_H
#define GAME_IMAGE_H

#include <cstdint>
#include <vector>

#include "player_types.h"
#include "utility.h"


using length_players_images_t = std::uint16_t;


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
};

#endif  // !GAME_IMAGE_H