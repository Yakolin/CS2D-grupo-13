#include "Equipment.h"

std::vector<WeaponImage> Equipment::get_weapons_image() {
    std::vector<WeaponImage> weapons;
    if (primary)
        weapons.push_back(primary->get_weapon_image());
    weapons.push_back(secondary->get_weapon_image());
    weapons.push_back(knife->get_weapon_image());
    return weapons;
}

// void Equipment::change_weapon() {}

void Equipment::drop_weapon(const player_id_t& player_id, IDroppableZone& droppeable_zone) {
    if (this->weapon_in_hand && *this->weapon_in_hand) {
        droppeable_zone.drop(player_id, *this->weapon_in_hand);
        this->weapon_in_hand =
                &this->secondary;  // esto deberia ser un metodo privado que me diga que arma sigue
    }
}
