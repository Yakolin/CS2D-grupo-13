#ifndef EQUIPEMENT_H_
#define EQUIPEMENT_H_

#include <memory>
#include <utility>

#include "FireableWeapon.h"
#include "Specials.h"
class Equipement {

public:
    Equipement():
            primary(nullptr),
            secondary(std::make_unique<Glock>()),
            knife(std::make_unique<Knife>()),
            bomb(nullptr) {}
    std::unique_ptr<Weapon> primary;
    std::unique_ptr<Weapon> secondary;
    std::unique_ptr<Weapon> knife;
    std::unique_ptr<Weapon> bomb;
    void put_bomb(std::unique_ptr<Weapon>& bomb);

    /*
        change_weapon();
        drop_weapon();
    */
};

#endif  // EQUIPEMENT_H_
