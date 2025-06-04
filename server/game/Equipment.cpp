#include "Equipment.h"

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
    uint16_t price = 0;
    switch (weapon_code) {
        case WeaponCode::AK47:
            price = 500;  // Aca es mejor manejar precios asociados al YAML y no al arma en si
            if (money < price)
                break;
            primary = std::make_unique<Ak47>();
            break;
        default:
            return;
    }
    std::cout << "Arma comprada con éxito.\n";
}
void Equipment::reset_equipment() {
    primary = nullptr;
    secondary = nullptr;
    secondary = std::make_unique<Glock>();
}

void Equipment::drop_weapon(const player_id_t& player_id) {
    if (this->weapon_in_hand && *this->weapon_in_hand) {
        if (this->weapon_in_hand->get()->is_droppable()) {
            this->droppable_zone.drop(player_id, *this->weapon_in_hand);
            this->new_weapon_in_hand(this->secondary);
            this->primary = std::make_unique<NullWeapon>();
        }
    }
}

void Equipment::reload() { this->weapon_in_hand->get()->reload(); }

void Equipment::shoot(const player_id_t& player_id, Position& position) {
    this->weapon_in_hand->get()->set_on_action(this->spawneable_zone, player_id, position);
}

std::vector<WeaponImage> Equipment::get_weapons_image() {
    std::vector<WeaponImage> weapons;
    if (primary)
        weapons.push_back(primary->get_weapon_image());
    weapons.push_back(secondary->get_weapon_image());
    weapons.push_back(knife->get_weapon_image());
    return weapons;
}
