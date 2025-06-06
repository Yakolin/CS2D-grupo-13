#include "Equipment.h"

Equipment::Equipment(const player_id_t& player_id, ISpawneableZone& spawneable_zone,
                     IDroppableZone& droppable_zone, WeaponFactory& weapon_factory):
        player_id(player_id),
        spawneable_zone(spawneable_zone),
        droppable_zone(droppable_zone),
        weapon_factory(weapon_factory),
        primary(nullptr),
        secondary(weapon_factory.weapon_create(WeaponCode::GLOCK)),
        knife(weapon_factory.weapon_create(WeaponCode::KNIFE)),
        weapon_in_hand(&this->secondary) {}

Equipment::~Equipment() {}

void Equipment::new_weapon_in_hand(std::unique_ptr<Weapon>& weapon) {
    this->weapon_in_hand = &weapon;
}

void Equipment::change_weapon(const EquipType& equip) {
    switch (equip) {
        case EquipType::KNIFE:
            this->new_weapon_in_hand(this->knife);
            break;
        case EquipType::SECONDARY:
            this->new_weapon_in_hand(this->secondary);
            break;
        case EquipType::PRIMARY:
            this->new_weapon_in_hand(this->primary);
            break;
        default:
            break;
    }
}


void Equipment::buy_weapon_by_code(const WeaponCode& weapon_code, uint16_t money) {
    if (weapon_factory.price_weapon(weapon_code) > money)
        return;
    primary = weapon_factory.weapon_create(weapon_code);
}
void Equipment::reset_equipment() {
    primary = nullptr;
    secondary = nullptr;
    secondary = weapon_factory.weapon_create(WeaponCode::GLOCK);
    bomb.reset();
}

void Equipment::drop_weapon() {
    if (primary)
        droppable_zone.drop(this->player_id, primary);
    /*
    if (this->weapon_in_hand && *this->weapon_in_hand) {
        if (this->weapon_in_hand->get()->is_droppable()) {
            this->droppable_zone.drop(this->player_id, *this->weapon_in_hand);
            this->new_weapon_in_hand(this->secondary);
            this->primary = std::make_unique<NullWeapon>();
        }
    }
    */
}

void Equipment::reload() { this->weapon_in_hand->get()->reload(); }

void Equipment::shoot(Position& position) {
    if (/*Weapon in hand es bomba*/ bomb.lock()) {
        droppable_zone.plant_bomb(player_id);
    } else {
        this->secondary->set_on_action(this->spawneable_zone, this->player_id, position);
    }
}

std::vector<WeaponImage> Equipment::get_weapons_image() {
    std::vector<WeaponImage> weapons;
    if (primary)
        weapons.push_back(primary->get_weapon_image());
    weapons.push_back(secondary->get_weapon_image());
    weapons.push_back(knife->get_weapon_image());
    return weapons;
}
bool Equipment::equip_weapon(std::unique_ptr<Weapon>& weapon) {
    if (!primary) {
        primary = std::move(weapon);
        return true;
    }
    return false;
}
void Equipment::equip_bomb(std::weak_ptr<Bomb> new_bomb) {
    bomb = new_bomb;
    if (bomb.lock())
        bomb.lock()->set_equiped();
}
