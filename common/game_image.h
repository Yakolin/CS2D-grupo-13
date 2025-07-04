#ifndef GAME_IMAGE_H
#define GAME_IMAGE_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "game_info.h"
#include "player_command_types.h"
#include "sound_image.h"
#include "utility.h"

using coordinate_t = std::uint16_t;
using health_t = std::uint8_t;
using deaths_t = std::uint8_t;
using points_t = std::uint16_t;
using length_players_images_t = std::uint16_t;
using length_weapons_images_t = std::uint8_t;
using length_bullets_in_air_t = std::uint16_t;
using length_weapons_dropped_t = std::uint8_t;
using length_heared_sounds_t = std::uint8_t;
using bomb_state_t = std::uint8_t;
using team_t = std::uint8_t;
using game_state_t = std::uint8_t;
using round_time_t = std::uint16_t;
using round_t = std::uint8_t;
using money_t = std::uint16_t;
using bullet_t = std::uint8_t;
using magazine_t = std::uint8_t;

enum class GameState {
    TIME_TO_BUY,
    ROUND_STARTED,
    GAME_STARTED,
    GAME_ENDED,
    TT_WIN_ROUND,
    CT_WIN_ROUND,
    NONE,
    TT_WIN_GAME,
    CT_WIN_GAME
};
enum class Team { CT, TT };
enum class BombState { EQUIPED, DROPPED, ACTIVATED, DESACTIVATED, EXPLOTED };

class BulletImage {
public:
    Position initial;
    Position end;
    uint8_t width;
    WeaponCode code;
    BulletImage(const Position& initial, const Position& end, uint8_t width, WeaponCode code):
            initial(initial), end(end), width(width), code(code) {}
    ~BulletImage() {}
};

class BombImage {  // esto deberia tener un ennum de estado BombState que puede ser dropped o
                   // activate o lo que sea
public:
    BombImage() = default;
    BombImage(Position pos, BombState state): position(pos), state(state) {}
    WeaponCode weapon_code = WeaponCode::BOMB;
    Position position;
    BombState state = BombState::DROPPED;
};

class WeaponDropped {
public:
    WeaponDropped(WeaponCode weapon_code, Position pos): weapon_code(weapon_code), position(pos) {}
    WeaponCode weapon_code;
    Position position;
};
class WeaponImage {
public:
    WeaponCode weapon_code;
    bullet_t current_bullets;
    magazine_t magazine;

    WeaponImage(WeaponCode weapon_code, bullet_t current_bullets, magazine_t magazine):
            weapon_code(weapon_code), current_bullets(current_bullets), magazine(magazine) {}
};
class PlayerImage {
public:
    player_id_t player_id;
    Position position;
    health_t health;
    deaths_t deaths;
    deaths_t kills;
    points_t points;
    money_t money;
    money_t collected_money;
    WeaponCode equipped_weapon;
    std::vector<WeaponImage> weapons;
    SoundImage heared_sounds;
    Team team;
    Position mouse_position;
    Skins skin;
    PlayerImage(const player_id_t& player_id, const Position& position, const int& health,
                const int& deaths, const int& kills, const int& points, const money_t money,
                const money_t collected_money, const WeaponCode equipped_weapon,
                std::vector<WeaponImage>&& weapons, const Team& team,
                const Position& mouse_position, const Skins& skin, SoundImage&& heared_sounds):
            player_id(player_id),
            position(position),
            health(health),
            deaths(deaths),
            kills(kills),
            points(points),
            money(money),
            collected_money(collected_money),
            equipped_weapon(equipped_weapon),
            weapons(std::move(weapons)),
            heared_sounds(std::move(heared_sounds)),
            team(team),
            mouse_position(mouse_position),
            skin(skin) {}
    ~PlayerImage() = default;
};

class GameStateImage {
public:
    GameState state = GameState::NONE;
    round_time_t time = 0;
    round_t round = 0;

    GameStateImage() = default;
    GameStateImage(GameState state, round_time_t time, round_t round):
            state(state), time(time), round(round) {}
    ~GameStateImage() = default;
};

class GameImage {
public:
    GameImage() = default;
    ~GameImage() = default;

    player_id_t client_id = 0;
    std::vector<PlayerImage> players_images;
    std::vector<BulletImage> bullets_in_air;
    BombImage bomb;
    std::vector<WeaponDropped> dropped_things;
    GameStateImage game_state;
};

#endif  // !GAME_IMAGE_H
