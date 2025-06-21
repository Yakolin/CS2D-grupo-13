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

using damage_t = uint8_t;
using range_t = uint8_t;  // tal vez deberia ser uint16
using width_t = uint8_t;

class Weapon: public IInteractuable {

protected:
    damage_t damage;
    range_t range;
    width_t width;
    std::unique_ptr<FireMode> fire_mode;

    virtual damage_t calculate_damage(float distance) = 0;

    WeaponCode get_weapon_code() { return IInteractuable::get_weapon_code(); }

public:
    explicit Weapon(WeaponCode code, damage_t damage, range_t range, width_t width,
                    std::unique_ptr<FireMode>&& fire_mode):
            IInteractuable(code),
            damage(damage),
            range(range),
            width(width),
            fire_mode(std::move(fire_mode)) {}
    virtual ~Weapon() = default;

    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override = 0;

    virtual bool shoot_burst(ISpawneableZone& spawn, player_id_t id,
                             Position& direction) override = 0;
    virtual void reload() override = 0;
    virtual bool is_droppable() = 0;
    virtual WeaponImage get_weapon_image() = 0;
};

#endif  //  WEAPON_H_
