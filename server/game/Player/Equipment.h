#ifndef EQUIPMENT_H_
#define EQUIPMENT_H_

#include <memory>
#include <utility>
#include <vector>

#include "../../../common/player_command_types.h"
#include "../Map/IDroppableZone.h"
#include "../Map/ISoundZone.h"
#include "../Map/ISpawneableZone.h"
#include "../Weapons/FireableWeapon.h"
#include "../Weapons/Guns/NullWeapon.h"
#include "../Weapons/IInteractuable.h"
#include "../Weapons/SpecialWeapons.h"
#include "../Weapons/WeaponFactory.h"

class Equipment {
private:
    const player_id_t& player_id;

    ISpawneableZone& spawneable_zone;
    IDroppableZone& droppable_zone;
    ISoundZone& sound_zone;
    WeaponFactory& weapon_factory;

    std::shared_ptr<FireableWeapon> primary;
    std::shared_ptr<FireableWeapon> secondary;
    std::shared_ptr<Weapon> knife;
    std::weak_ptr<Bomb> bomb;
    std::shared_ptr<IInteractuable> weapon_in_hand;
    void new_weapon_in_hand(const std::shared_ptr<IInteractuable>& weapon);
    void equip_bomb(std::weak_ptr<Bomb> new_bomb);

public:
    Equipment(const player_id_t& player_id, ISpawneableZone& spawneable_zone,
              IDroppableZone& droppable_zone, ISoundZone& sound_zone,
              WeaponFactory& weapon_factory);
    ~Equipment();

    Equipment(Equipment&&) = default;
    Equipment& operator=(Equipment&&) = default;
    Equipment(const Equipment&) = delete;
    Equipment& operator=(const Equipment&) = delete;

    void change_weapon(const EquipType& equip_type);
    void buy_weapon_by_code(const WeaponCode& weapon_code, money_t& money);
    void reset_equipment();
    void restore();
    void drop_weapon();
    void reload();
    void shoot(Position& position);
    void shoot_burst(Position& position);
    bool equip_droppable(const std::shared_ptr<IInteractuable>& droppable);
    void drop_all();
    std::vector<WeaponImage> get_weapons_image();
    WeaponCode get_equiped_code();
};

#endif  // EQUIPMENT_H_
