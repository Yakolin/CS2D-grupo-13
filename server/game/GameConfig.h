#ifndef GAME_CONFIG_H_
#define GAME_CONFIG_H_
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <yaml-cpp/yaml.h>

#include "../../common/player_command_types.h"
class GameConfig {
public:
    typedef struct WeaponConfig {
        uint16_t price;
        uint8_t damage;
        uint8_t fire_rate;
        uint8_t max_b;
        uint8_t current_b;
    } weapon_config_t;

    std::map<WeaponCode, WeaponConfig> weapon_configs;
    typedef struct TimerConfig {
        int time_buy;
        int time_round;
        int time_after_round;
        int time_bomb;
    } timer_config_t;
    TimerConfig timer_config;

private:
    WeaponCode weapon_name_to_code(const std::string& name);
    void load_weapons(const YAML::Node& config);
    void load_timers(const YAML::Node& config);
    void load(const std::string& file_path);

    void calculate_tile_size(const int& cols, const int& rows);

public:
    GameConfig();
    std::map<WeaponCode, WeaponConfig>& get_weapon_config() { return weapon_configs; }
    TimerConfig& get_timer_config() { return timer_config; }
};

#endif  // GAME_CONFIG_H_
