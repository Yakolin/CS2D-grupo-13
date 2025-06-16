#ifndef GAME_CONFIG_H_
#define GAME_CONFIG_H_
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <yaml-cpp/yaml.h>

#include "../../../common/game_image.h"
#include "../../../common/game_info.h"
#include "../../../common/player_command_types.h"

// Weapons
using price_t = uint16_t;
using damage_t = uint8_t;
using fire_rate_t = uint8_t;
using max_bullets_t = uint8_t;
using current_bullets_t = uint8_t;
using width_t = uint8_t;
using distance_t = uint8_t;


// Player
using earned_points_t = uint16_t;
using multiplier_points_t = uint16_t;

class GameConfig {
public:
    typedef struct WeaponConfig {
        price_t price;
        damage_t damage;
        fire_rate_t fire_rate;
        max_bullets_t max_b;
        current_bullets_t current_b;
        width_t width;
        distance_t distance;
        bool purchasable;
    } weapon_config_t;

    std::map<WeaponCode, WeaponConfig> weapon_configs;
    typedef struct TimerConfig {
        int time_buy;
        int time_round;
        int time_bomb;
        int time_ending;
    } timer_config_t;
    TimerConfig timer_config;

    typedef struct PlayerConfig {
        health_t health;
        money_t money;
        points_t points;
        earned_points_t earned_points;
        multiplier_points_t multiplier_points;
    } player_config_t;
    PlayerConfig player_config;
    uint8_t dropped_weapons;

private:
    WeaponCode weapon_name_to_code(const std::string& name);
    void load_weapons(const YAML::Node& config);
    void load_timers(const YAML::Node& config);
    void load_player(const YAML::Node& config);
    void load_general_configs(const YAML::Node& config);
    void load(const std::string& file_path);

public:
    GameConfig();
    std::map<WeaponCode, WeaponConfig>& get_weapon_config() { return weapon_configs; }
    TimerConfig& get_timer_config() { return timer_config; }
    PlayerConfig& get_player_config() { return player_config; }
    std::vector<WeaponInfo> get_info_weapons();
};

#endif  // GAME_CONFIG_H_
