
#ifndef FIREABLE_WEAPON_H_
#define FIREABLE_WEAPON_H_

//  "Copyright 2025 Yaco Santamarina"
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "TimerWeapons.h"
#include "Weapon.h"
class FireableWeapon: public Weapon {
    max_bullets_t inventory_bullets;
    max_bullets_t magazine;

protected:
    TimerWeapons timer;
    void reduce_bullets();
    bool have_bullets();

public:
    FireableWeapon(WeaponCode code, GameConfig::weapon_config_t specs):
            Weapon(code, specs),
            inventory_bullets(specs.max_b),
            magazine(specs.current_b),
            timer(specs.timer_fire) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override = 0;
    virtual void reload() override;
    virtual void restore_bullets() override;
    virtual WeaponImage get_weapon_image() override;
};
class Ak47: public FireableWeapon {
private:
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
