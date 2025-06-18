#ifndef SPECIAL_WEAPONS_H_
#define SPECIAL_WEAPONS_H_
#include "../../../common/game_image.h"
#include "../Timer.h"

#include "IInteractuable.h"

class Bomb: public IInteractuable {
private:
    Timer& timer;
    BombState state = BombState::EQUIPED;

public:
    explicit Bomb(Timer& timer): IInteractuable(WeaponCode::BOMB), timer(timer) {}
    virtual bool set_on_action(ISpawneableZone& spawn, player_id_t id,
                               [[maybe_unused]] Position& direction) override;
    bool shoot_burst(ISpawneableZone& spawn, player_id_t, Position& direction) override;
    virtual void reload() override {}
    void defuse();
    void set_equiped();
    void set_unequiped();
    void set_exploted();
    bool is_equiped();
    bool is_activate();
    bool is_defused();
    BombState get_state() { return state; }
    WeaponImage get_weapon_image();
};

#endif  // SPECIAL_WEAPONS_H_
