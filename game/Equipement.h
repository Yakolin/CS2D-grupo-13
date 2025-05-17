#ifndef EQUIPEMENT_H_
#define EQUIPEMENT_H_

#include <memory>
#include <utility>

#include "FireableWeapon.h"
#include "Specials.h"
class Equipement {
    std::unique_ptr<Weapon> primary;
    std::unique_ptr<Weapon> secondary;
    std::unique_ptr<Weapon> knife;
    std::unique_ptr<Weapon> bomb;

    // std::unique_ptr<Weapon> current_weapon;
public:
    Equipement():
            primary(nullptr),
            secondary(std::unique_ptr<Glock>()),
            knife(std::unique_ptr<Knife>()),
            bomb(nullptr) {}

    void put_bomb(std::unique_ptr<Weapon>& bomb);

    /*
        fire_current_weapon();
        reload_current_weapon();
        change_weapon();
        drop_weapon();
    */
};

#endif  // EQUIPEMENT_H_
