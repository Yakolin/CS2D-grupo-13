#ifndef NULL_WEAPON_H
#define NULL_WEAPON_H

#include "../../Config/GameConfig.h"
#include "../FireableWeapon.h"
#include "FireMode/SemiAutomatic.h"

class NullWeapon: public Weapon {
public:
    NullWeapon(): Weapon(WeaponCode::NONE, 0, 0, 0, std ::make_unique<SemiAutomatic>(0)) {}
    ~NullWeapon() = default;

    bool set_on_action([[maybe_unused]] ISpawneableZone& spawn, [[maybe_unused]] player_id_t id,
                       [[maybe_unused]] Position& direction) override {
        return false;
    }

    bool shoot_burst([[maybe_unused]] ISpawneableZone& spawn, [[maybe_unused]] player_id_t id,
                     [[maybe_unused]] Position& direction) override {
        return false;
    }


    void reload() override {}
    WeaponImage get_weapon_image() override { return WeaponImage(WeaponCode::NONE, 0, 0); }
    bool is_droppable() override { return false; }
};


#endif  // !NULL_WEAPON_H