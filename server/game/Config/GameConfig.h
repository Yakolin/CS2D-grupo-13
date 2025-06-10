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

#include "../../../common/game_info.h"
#include "../../../common/player_command_types.h"
class GameConfig {
public:
    typedef struct WeaponConfig {
        uint16_t price;
        uint8_t damage;
        uint8_t fire_rate;
        uint8_t max_b;
        uint8_t current_b;
        uint8_t width;
        uint8_t distance;
    } weapon_config_t;

    std::map<WeaponCode, WeaponConfig> weapon_configs;
    typedef struct TimerConfig {
        int time_buy;
        int time_round;
        int time_after_round;
        int time_bomb;
        int time_ending;
    } timer_config_t;
    TimerConfig timer_config;

    typedef struct PlayerConfig {
        uint8_t health;
        uint16_t money;
        uint16_t points;
        uint16_t earned_points;
        uint8_t multiplier_points;
    } player_config_t;
    PlayerConfig player_config;

private:
    WeaponCode weapon_name_to_code(const std::string& name);
    void load_weapons(const YAML::Node& config);
    void load_timers(const YAML::Node& config);
    void load_player(const YAML::Node& config);
    void load(const std::string& file_path);

public:
    GameConfig();
    std::map<WeaponCode, WeaponConfig>& get_weapon_config() { return weapon_configs; }
    TimerConfig& get_timer_config() { return timer_config; }
    PlayerConfig& get_player_config() { return player_config; }
    std::vector<WeaponInfo> get_info_weapons();
};

#endif  // GAME_CONFIG_H_
