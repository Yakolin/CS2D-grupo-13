#ifndef EQUIPMENT_H_
#define EQUIPMENT_H_

#include <memory>
#include <utility>
#include <vector>

#include "../../common/player_command_types.h"

#include "FireableWeapon.h"
#include "IDropeableZone.h"
#include "SpecialWeapons.h"

class Equipment {
public:
    Equipment():
            primary(nullptr),
            secondary(std::make_unique<Glock>()),
            knife(std::make_unique<Knife>()),
            weapon_in_hand(&this->secondary) {}
    std::unique_ptr<Weapon> primary;
    std::unique_ptr<Weapon> secondary;
    std::unique_ptr<Weapon> knife;
    std::unique_ptr<Weapon>* weapon_in_hand;


    // void change_weapon(EquipType& equip_type);

    void drop_weapon(const player_id_t& player_id, IDroppableZone& droppeable_zone);
    std::vector<WeaponImage> get_weapons_image();
};

#endif  // EQUIPMENT_H_
