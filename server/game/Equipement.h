#ifndef EQUIPEMENT_H_
#define EQUIPEMENT_H_

#include <memory>
#include <utility>
#include <vector>

#include "FireableWeapon.h"
#include "SpecialWeapons.h"
class Equipement {

public:
    Equipement():
            primary(nullptr),
            secondary(std::make_unique<Glock>()),
            knife(std::make_unique<Knife>()) {}
    std::unique_ptr<Weapon> primary;
    std::unique_ptr<Weapon> secondary;
    std::unique_ptr<Weapon> knife;
    // std::unique_ptr<Weapon> bomb;

    /*
        change_weapon();
        drop_weapon();
    */
    std::vector<WeaponImage> get_weapons_image();
};

#endif  // EQUIPEMENT_H_
