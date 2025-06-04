#ifndef SpecialWeapons_H_
#define SpecialWeapons_H_
#include "Timer.h"
#include "Weapon.h"

class Bomb {
private:
    Timer& timer;

public:
    explicit Bomb(Timer& timer): timer(timer) {}
    void set_on_bomb();
    WeaponImage get_weapon_image();
};

class Knife: public Weapon {
public:
    Knife(): Weapon(WeaponCode::KNIFE) {}
    virtual void set_on_action(ISpawneableZone& spawn, player_id_t id,
                               Position& direction) override;
    virtual void reload() override;
    virtual WeaponImage get_weapon_image() override;
    virtual bool is_droppable() override;
};

#endif  // SpecialWeapons_H_
