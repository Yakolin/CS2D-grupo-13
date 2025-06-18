#ifndef WEAPON_CONFIG_H
#define WEAPON_CONFIG_H

#include <string>

#include <yaml-cpp/yaml.h>

class WeaponConfig {
private:
    YAML::Node weapon_config;

public:
    static WeaponConfig& get_instance() {
        static WeaponConfig instance;
        return instance;
    }

    void load(const std::string& filename) { weapon_config = YAML::LoadFile(filename); }

    YAML::Node operator[](const std::string& key) const { return this->weapon_config[key]; }

    ~WeaponConfig() {};
};


#endif  // !WEAPON_CONFIG_H