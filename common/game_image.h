#ifndef GAME_IMAGE_H
#define GAME_IMAGE_H

#include <cstdint>
#include <string>
#include <vector>

#include "player_command_types.h"
#include "utility.h"

using coordinate_t = std::uint16_t;
using health_t = std::uint8_t;
using points_t = std::uint8_t;
using length_players_images_t = std::uint16_t;

enum class Team { CT, TT };


class WeaponImage {
    WeaponCode weapon_code;
    uint8_t bullets;
    uint8_t magazine;
    uint8_t current_bullets;
};
class PlayerImage {
public:
    player_id_t player_id;
    Position position;
    health_t health;
    points_t points;
    std::vector<WeaponImage> weapons;
    // Aca falta el tema del equipement y las armas
    PlayerImage(player_id_t player_id, Position position, int health, int points):
            player_id(player_id), position(position), health(health), points(points) {}
    ~PlayerImage() = default;
};

class GameImage {
public:
    GameImage() = default;
    ~GameImage() = default;

    player_id_t client_id = 0;
    std::vector<PlayerImage> players_images;
    uint8_t time = 0;
    uint8_t round = 0;
    std::string pathname_walls;  // Este deberia de enviarse UNICAMENTE una vez!
    // Balas en el aire
    // Bomba
    // Drops
    // Sonidos)?
};

#endif  // !GAME_IMAGE_H
