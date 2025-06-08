#ifndef WEAPON_H_
#define WEAPON_H_

#include <map>
#include <memory>

#include "../../../common/game_image.h"
#include "../../../common/player_command_types.h"
#include "../Colliders/Colliders.h"
#include "../Map/ISpawneableZone.h"

#include "IDroppable.h"

class Weapon: public IDroppable {
public:
    typedef struct WeaponSpecs {
        uint16_t price;
        uint16_t damage;
        uint8_t fire_rate;
        uint8_t inventory_bullets;
        uint8_t current_bullets;
        uint8_t magazine;
    } weapon_specs_t;
    weapon_specs_t specs;
    explicit Weapon(WeaponCode code, weapon_specs_t specs): IDroppable(code), specs(specs) {}
    virtual ~Weapon() = default;

    virtual void set_on_action(
            ISpawneableZone& spawn, player_id_t id,
            Position& direction) = 0;  // Recordatorio de este = 0. Significa que es puro
    virtual void reload() = 0;
    virtual WeaponImage get_weapon_image() = 0;
    virtual bool is_droppable() = 0;
};

class NullWeapon: public Weapon {
public:
    NullWeapon(): Weapon(WeaponCode::NONE, {0, 0, 0, 0, 0, 0}) {}
    ~NullWeapon() = default;

    virtual void set_on_action([[maybe_unused]] ISpawneableZone& spawn,
                               [[maybe_unused]] player_id_t id,
                               [[maybe_unused]] Position& direction) override {}
    void reload() override {}
    WeaponImage get_weapon_image() override { return WeaponImage(WeaponCode::NONE, 0, 0, 0); }
    bool is_droppable() override { return false; }
};


#endif  //  WEAPON_H_
