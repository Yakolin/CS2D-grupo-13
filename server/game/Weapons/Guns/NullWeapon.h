#ifndef NULL_WEAPON_H
#define NULL_WEAPON_H

#include "../../Config/GameConfig.h"
#include "../FireableWeapon.h"
#include "FireMode/SemiAutomatic.h"

class NullWeapon: public FireableWeapon {

private:
    damage_t calculate_damage(float distance [[maybe_unused]]) override { return 0; }

public:
    NullWeapon():
            FireableWeapon(WeaponCode::NONE, 0, 0, 0, 0, std ::make_unique<SemiAutomatic>(0), 0,
                           0) {}
    ~NullWeapon() = default;


    bool reload() override { return false; }

    bool set_on_action([[maybe_unused]] ISpawneableZone& spawn, [[maybe_unused]] player_id_t id,
                       [[maybe_unused]] Position& direction) override {
        return false;
    }

    bool shoot_burst([[maybe_unused]] ISpawneableZone& spawn, [[maybe_unused]] player_id_t id,
                     [[maybe_unused]] Position& direction) override {
        return false;
    }

    bool is_droppable() override { return false; }
};


#endif  // !NULL_WEAPON_H