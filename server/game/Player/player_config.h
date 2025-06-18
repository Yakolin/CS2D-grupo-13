#ifndef PLAYER_CONFIG_H
#define PLAYER_CONFIG_H

#include <string>

#include <yaml-cpp/yaml.h>

class PlayerConfig {
private:
    YAML::Node player_config;

public:
    static PlayerConfig& get_instance() {
        static PlayerConfig instance;
        return instance;
    }

    void load(const std::string& filename) { player_config = YAML::LoadFile(filename); }

    YAML::Node operator[](const std::string& key) const { return this->player_config[key]; }

    ~PlayerConfig() {};
};

#endif  // !PLAYER_CONFIG_H
