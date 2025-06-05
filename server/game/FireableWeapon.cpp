#include "FireableWeapon.h"
void Glock::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (current_bullets > 0) {
        uint8_t bullets_fired = std::min(current_bullets, fire_rate);
        current_bullets -= bullets_fired;
        auto calculate_damage_func = [this](float distance) {
            return this->calculate_damage(distance);
        };
        ISpawneableZone::collider_solicitude_t wanted = {2, 5, direction, calculate_damage_func};
        spawn.spawn_collider(id, wanted);
    }
}
bool Glock::is_droppable() { return false; }

uint8_t Glock::calculate_damage(float distance) { return 8 * distance; }

uint8_t Ak47::calculate_damage(float distance) { return 1 * distance; }
void Ak47::set_on_action(ISpawneableZone& spawn, player_id_t id,
                         Position& direction) {  // Es un calco por ahora
    if (current_bullets > 0) {
        uint8_t bullets_fired = std::min(current_bullets, fire_rate);
        current_bullets -= bullets_fired;
        auto calculate_damage_func = [this](float distance) {
            return this->calculate_damage(distance);
        };
        ISpawneableZone::collider_solicitude_t wanted = {2, 25, direction, calculate_damage_func};
        spawn.spawn_collider(id, wanted);
    }
}

bool Ak47::is_droppable() { return true; }

void FireableWeapon::reload() {
    if (inventory_bullets > 0 &&
        current_bullets < magazine) {  // Si en el inventario tengo >= 0 balas
        uint8_t needed_bullets = magazine - current_bullets;
        uint8_t avalible_bullets = std::min(needed_bullets, inventory_bullets);
        current_bullets += avalible_bullets;
        inventory_bullets -= avalible_bullets;
        std::cout << "Recargas : " << avalible_bullets
                  << " balas. Balas restantes en almacenamiento: " << inventory_bullets
                  << std::endl;
    } else {
        std::cout << "No tenes mas balas en el almacenamiento\no no habia porque recargar, ya "
                     "estas lleno\n";
    }
}
WeaponImage FireableWeapon::get_weapon_image() {
    /* Aca deberia de encargarse cada arma de esto...*/
    return WeaponImage(code, current_bullets, magazine, inventory_bullets);
}
