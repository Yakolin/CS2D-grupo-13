
#ifndef FIREABLE_WEAPON_H_
#define FIREABLE_WEAPON_H_

//  "Copyright 2025 Yaco Santamarina"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "Weapon.h"
class FireableWeapon: public Weapon {
    max_bullets_t inventory_bullets;
    max_bullets_t magazine;

protected:
    bool reduce_bullets();

public:
    FireableWeapon(WeaponCode code, GameConfig::weapon_config_t specs):
            Weapon(code, specs), inventory_bullets(specs.max_b), magazine(specs.current_b) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override = 0;
    virtual void reload() override;
    virtual void restore_bullets() override;
    virtual WeaponImage get_weapon_image() override;
};
class Ak47: public FireableWeapon {

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

private:
    int bullets_in_burst = 0;
    Clock burst_timer;
    Clock shot_timer;
    const int max_burst = 3;                 // cantidad de balas por rafaga
    const float time_between_shoots = 0.4f;  // tiempo entre balas
    const float burst_coldown = 1.8f;        // tiempo hasta la siguiente rafaga

    uint8_t calculate_damage(float distance);

public:
    explicit Ak47(GameConfig::weapon_config_t specs): FireableWeapon(WeaponCode::AK47, specs) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual bool is_droppable() override;
};
class Glock: public FireableWeapon {
private:
    uint8_t calculate_damage(float distance);

public:
    explicit Glock(GameConfig::weapon_config_t specs): FireableWeapon(WeaponCode::GLOCK, specs) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual bool is_droppable() override;
};
class M3: public FireableWeapon {
private:
    uint8_t calculate_damage(float distance);

public:
    explicit M3(GameConfig::weapon_config_t specs): FireableWeapon(WeaponCode::M3, specs) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual bool is_droppable() override;
};
class AWP: public FireableWeapon {
private:
    uint8_t calculate_damage(float distance);

public:
    explicit AWP(GameConfig::weapon_config_t specs): FireableWeapon(WeaponCode::AWP, specs) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual bool is_droppable() override;
};
class Knife: public Weapon {
public:
    explicit Knife(GameConfig::weapon_config_t specs): Weapon(WeaponCode::KNIFE, specs) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual void reload() override;
    virtual void restore_bullets() override {}  // Quiza aca no deberia ir esto... desp lo veo bien
    virtual WeaponImage get_weapon_image() override;
    virtual bool is_droppable() override;
};

#endif  // FIREABLE_WEAPON_H_
