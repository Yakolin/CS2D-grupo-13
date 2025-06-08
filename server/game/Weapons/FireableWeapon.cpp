#include "FireableWeapon.h"
bool Glock::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (specs.current_bullets > 0) {
        uint8_t bullets_fired = std::min(specs.current_bullets, specs.fire_rate);
        specs.current_bullets -= bullets_fired;
        auto calculate_damage_func = [this](float distance) {
            return this->calculate_damage(distance);
        };
        ISpawneableZone::collider_solicitude_t wanted = {2, 5, direction, calculate_damage_func};
        spawn.spawn_collider(id, wanted);
    }
    return true;
}
bool Glock::is_droppable() { return false; }

uint8_t Glock::calculate_damage(float distance) { return specs.damage * distance; }

uint8_t Ak47::calculate_damage(float distance) { return specs.damage * distance; }

bool Ak47::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (specs.current_bullets > 0) {
        uint8_t bullets_fired = std::min(specs.current_bullets, specs.fire_rate);
        specs.current_bullets -= bullets_fired;
        auto calculate_damage_func = [this](float distance) {
            return this->calculate_damage(distance);
        };
        ISpawneableZone::collider_solicitude_t wanted = {2, 25, direction, calculate_damage_func};
        spawn.spawn_collider(id, wanted);
    }
    return true;
}

bool Ak47::is_droppable() { return true; }

void FireableWeapon::reload() {
    if (specs.inventory_bullets > 0 &&
        specs.current_bullets < specs.magazine) {  // Si en el inventario tengo >= 0 balas
        uint8_t needed_bullets = specs.magazine - specs.current_bullets;
        uint8_t avalible_bullets = std::min(needed_bullets, specs.inventory_bullets);
        specs.current_bullets += avalible_bullets;
        specs.inventory_bullets -= avalible_bullets;
    }
}
WeaponImage FireableWeapon::get_weapon_image() {
    /* Aca deberia de encargarse cada arma de esto...*/
    return WeaponImage(code, specs.current_bullets, specs.magazine, specs.inventory_bullets);
}


/* KNIFE */
bool Knife::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    auto function_damage = [this]([[maybe_unused]] float distance) { return specs.damage; };
    ISpawneableZone::collider_solicitude_t wanted = {
            2, 2, direction, function_damage};  // Es muy cercano, asi que 2 esta bien)?
                                                // Aclaracion: aca de manejarlo el config
    spawn.spawn_collider(id, wanted);
    return true;
}
void Knife::reload() { return; }
WeaponImage Knife::get_weapon_image() {
    return WeaponImage(code, 0, 0, 0);  // Aca evidentemente no maneja balas el cuchillo
}

bool Knife::is_droppable() { return false; }
