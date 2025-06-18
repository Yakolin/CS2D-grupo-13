#ifndef WEAPON_H_
#define WEAPON_H_

#include <map>
#include <memory>
#include <utility>

#include "../../../common/game_image.h"
#include "../../../common/player_command_types.h"
#include "../Colliders/Colliders.h"
#include "../Config/GameConfig.h"
#include "../Map/ISpawneableZone.h"
#include "Guns/FireMode/FireMode.h"

#include "IInteractuable.h"
class Weapon: public IInteractuable {

protected:
    std::unique_ptr<FireMode> fire_mode;

public:
    GameConfig::weapon_config_t specs;
    explicit Weapon(WeaponCode code, std::unique_ptr<FireMode>&& fire_mode,
                    GameConfig::weapon_config_t specs):
            IInteractuable(code), fire_mode(std::move(fire_mode)), specs(specs) {}
    virtual ~Weapon() = default;

    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override = 0;
    virtual void reload() override = 0;
    virtual void restore_bullets() = 0;
    virtual WeaponImage get_weapon_image() = 0;
    virtual bool is_droppable() = 0;
    virtual bool shoot_burst(ISpawneableZone& spawn, player_id_t id, Position& direction) override {
        this->fire_mode->fire_burst(spawn, id, direction);
    }
};

class NullWeapon: public Weapon {
public:
    NullWeapon(): Weapon(WeaponCode::NONE, std::make_unique <, {0, 0, 0, 0, 0, 0, 0, 0, 0}) {}
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
