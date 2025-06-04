#include "Equipement.h"

std::vector<WeaponImage> Equipement::get_weapons_image() {
    std::vector<WeaponImage> weapons;
    if (primary)
        weapons.push_back(primary->get_weapon_image());
    weapons.push_back(secondary->get_weapon_image());
    weapons.push_back(knife->get_weapon_image());
    return weapons;
}

void Equipement::buy_weapon_by_code(const WeaponCode& weapon_code, uint16_t money) {
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
void Equipement::reset_equipement() {
    primary = nullptr;
    secondary = nullptr;
    secondary = std::make_unique<Glock>();
}
