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
#include "WeaponFactory.h"

class Equipment {
private:
    const player_id_t& player_id;

    ISpawneableZone& spawneable_zone;
    IDroppableZone& droppable_zone;
    WeaponFactory& weapon_factory;

    std::unique_ptr<Weapon> primary;
    std::unique_ptr<Weapon> secondary;
    std::unique_ptr<Weapon> knife;
    std::weak_ptr<Bomb> bomb;
    std::unique_ptr<Weapon>* weapon_in_hand;
    void new_weapon_in_hand(std::unique_ptr<Weapon>& weapon);

public:
    Equipment(const player_id_t& player_id, ISpawneableZone& spawneable_zone,
              IDroppableZone& droppable_zone, WeaponFactory& weapon_factory);
    ~Equipment();

    Equipment(Equipment&&) = default;
    Equipment& operator=(Equipment&&) = default;
    Equipment(const Equipment&) = delete;
    Equipment& operator=(const Equipment&) = delete;

    void change_weapon(const EquipType& equip_type);
    void buy_weapon_by_code(const WeaponCode& weapon_code, uint16_t money);
    void reset_equipment();
    void drop_weapon();
    void reload();
    void shoot(Position& position);
    void equip_bomb(std::weak_ptr<Bomb> new_bomb);
    bool equip_weapon(std::unique_ptr<Weapon>& weapon);
    std::vector<WeaponImage> get_weapons_image();
};

#endif  // EQUIPMENT_H_
