#include "FireableWeapon.h"

void FireableWeapon::reload() {
    if (inventory_bullets > 0 && specs.current_b < magazine) {
        uint8_t needed_bullets = magazine - specs.current_b;
        uint8_t avalible_bullets = std::min(needed_bullets, inventory_bullets);
        specs.current_b += avalible_bullets;
        inventory_bullets -= avalible_bullets;
    }
}
void FireableWeapon::restore_bullets() {
    this->inventory_bullets = specs.max_b;
    specs.current_b = this->magazine;
}
WeaponImage FireableWeapon::get_weapon_image() {
    return WeaponImage(code, specs.current_b, magazine, inventory_bullets);
}
