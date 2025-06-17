#ifndef AK_H
#define AK_H

#include <chrono>

#include "../../Config/GameConfig.h"
#include "../FireableWeapon.h"

class Clock {
private:
    std::chrono::steady_clock::time_point start_time;

public:
    Clock() { start(); }

    void start() { start_time = std::chrono::steady_clock::now(); }


    bool elapsed(float seconds) const {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> diff = now - start_time;
        return diff.count() >= seconds;
    }

    float time_since_start() const {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> diff = now - start_time;
        return diff.count();
    }
};

class Ak47: public FireableWeapon {

private:
    int bullets_in_burst = 0;
    Clock burst_timer;
    Clock shot_timer;
    const int max_burst = 3;                 // cantidad de balas por rafaga
    const float time_between_shoots = 0.4f;  // tiempo entre balas
    const float burst_coldown = 1.8f;        // tiempo hasta la siguiente rafaga

    uint8_t calculate_damage(float distance);

public:
    explicit Ak47(GameConfig::weapon_config_t specs);
    ~Ak47();
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual bool is_droppable() override;
};

#endif  // !AK_H