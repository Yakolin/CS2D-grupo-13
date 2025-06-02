#include "Equipement.h"

std::vector<WeaponImage> Equipement::get_weapons_image(){
    std::vector<WeaponImage> weapons;
    if (primary) weapons.push_back(primary->get_weapon_image());
    if (secondary) weapons.push_back(secondary->get_weapon_image());
    return weapons;
}