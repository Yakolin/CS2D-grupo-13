#ifndef EQUIPMENT_H_
#define EQUIPMENT_H_

#include <memory>
#include <utility>
#include <vector>

#include "../../common/player_command_types.h"

#include "FireableWeapon.h"
#include "IDropeableZone.h"
#include "ISpawneableZone.h"
#include "SpecialWeapons.h"

class Equipment {
private:
    std::unique_ptr<Weapon> primary;
    std::unique_ptr<Weapon> secondary;
    std::unique_ptr<Weapon> knife;
    std::unique_ptr<Weapon>* weapon_in_hand;
    ISpawneableZone& spawneable_zone;
    IDroppableZone& droppable_zone;

    void new_weapon_in_hand(std::unique_ptr<Weapon>& weapon);

public:
    Equipment(ISpawneableZone& spawneable_zone, IDroppableZone& droppable_zone):
            primary(nullptr),
            secondary(std::make_unique<Glock>()),
            knife(std::make_unique<Knife>()),
            weapon_in_hand(&this->secondary),
            spawneable_zone(spawneable_zone),
            droppable_zone(droppable_zone) {}


    void change_weapon(const EquipType& equip_type);
    void buy_weapon_by_code(const WeaponCode& weapon_code, uint16_t money);
    void reset_equipment();
    void drop_weapon(const player_id_t& player_id);
    void reload();
    void shoot(const player_id_t& player_id, Position& position);
    std::vector<WeaponImage> get_weapons_image();
};

#endif  // EQUIPMENT_H_
