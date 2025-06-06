#ifndef GAME_IMAGE_H
#define GAME_IMAGE_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "player_command_types.h"
#include "utility.h"

using coordinate_t = std::uint16_t;
using health_t = std::uint8_t;
using points_t = std::uint8_t;
using length_players_images_t = std::uint16_t;

enum class Team { CT, TT };
class BombImage {
public:
    BombImage() = default;
    BombImage(Position pos, bool activate, bool dropped):
            position(pos), activate(activate), dropped(dropped) {}
    WeaponCode weapon_code = WeaponCode::BOMB;
    Position position = Position();
    bool activate = false;
    bool dropped = false;
};
class WeaponDropped {
public:
    WeaponDropped(WeaponCode weapon_code, Position pos): weapon_code(weapon_code), position(pos) {}
    WeaponCode weapon_code;
    Position position;
};
class WeaponImage {
public:
    WeaponImage(WeaponCode weapon_code, uint8_t current_bullets, uint8_t magazine,
                uint8_t inventory_bullets):
            weapon_code(weapon_code),
            current_bullets(current_bullets),
            magazine(magazine),
            inventory_bullets(inventory_bullets) {}
    WeaponCode weapon_code;
    uint8_t current_bullets;
    uint8_t magazine;
    uint8_t inventory_bullets;
};
class PlayerImage {
public:
    player_id_t player_id;
    Position position;
    health_t health;
    points_t points;
    std::vector<WeaponImage> weapons;
    Team team;
    // Aca falta el tema del equipement y las armas
    PlayerImage(player_id_t player_id, Position position, int health, int points,
                std::vector<WeaponImage>&& weapons, Team team):
            player_id(player_id),
            position(position),
            health(health),
            points(points),
            weapons(std::move(weapons)),
            team(team) {}
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

    // Balas en el aire
    BombImage bomb;
    std::vector<WeaponDropped> dropped_weapons;
};

#endif  // !GAME_IMAGE_H
