#ifndef WEAPON_H_
#define WEAPON_H_

#include <map>
#include <memory>

#include "../../../common/game_image.h"
#include "../../../common/player_command_types.h"
#include "../Colliders/Colliders.h"
#include "../Config/GameConfig.h"
#include "../Map/ISpawneableZone.h"

#include "IInteractuable.h"
#include "fire_mode.h"

using damage_t = uint8_t;

class Weapon {
protected:
    damage_t damage;
    std::unique_ptr<FireMode> mode;

public:
    explicit Weapon(damage_t damage, std::unique_ptr<FireMode> mode): damage(damage), mode(mode) {}

    virtual ~Weapon() = default;
    virtual void reload() = 0;
    virtual void restore_bullets() = 0;
    virtual WeaponImage get_weapon_image() = 0;
    virtual bool is_droppable() = 0;
    virtual void reset() = 0;
};

class NullWeapon: public Weapon {
public:
    NullWeapon(): Weapon(0, std::make_unique<SemiAutomatic>()) {}
    ~NullWeapon() = default;

    virtual bool set_on_action([[maybe_unused]] ISpawneableZone& spawn,
                               [[maybe_unused]] player_id_t id,
                               [[maybe_unused]] Position& direction) override {
        return false;
    }
    void reload() override {}
    void restore_bullets() override {}
    WeaponImage get_weapon_image() override { return WeaponImage(WeaponCode::NONE, 0, 0, 0); }
    bool is_droppable() override { return false; }
};


#endif  //  WEAPON_H_
