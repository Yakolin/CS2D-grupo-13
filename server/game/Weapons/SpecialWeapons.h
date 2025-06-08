#ifndef SPECIAL_WEAPONS_H_
#define SPECIAL_WEAPONS_H_
#include "../../../common/game_image.h"
#include "../Timer.h"

#include "IInteractuable.h"

class Bomb: public IInteractuable {
private:
    Timer& timer;
    bool equiped = false;
    bool activate = false;

public:
    explicit Bomb(Timer& timer): IInteractuable(WeaponCode::BOMB), timer(timer) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual void reload() override {}
    void set_equiped();
    void set_unequiped();
    bool is_equiped();
    bool is_activate();
    WeaponImage get_weapon_image();
};

#endif  // SPECIAL_WEAPONS_H_
