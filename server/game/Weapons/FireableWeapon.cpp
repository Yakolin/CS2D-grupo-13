#include "FireableWeapon.h"

#include <thread>
bool Glock::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (have_bullets() && timer.can_shoot()) {
        reduce_bullets();
        timer.start();
        auto calculate_damage_func = [this](float distance) {
            return this->calculate_damage(distance);
        };
        ISpawneableZone::collider_solicitude_t wanted = {specs.width, specs.distance, direction,
                                                         calculate_damage_func};
        spawn.spawn_collider(id, wanted);
    }
    return true;
}
bool Glock::is_droppable() { return false; }

uint8_t Glock::calculate_damage(float distance) { return specs.damage * distance; }

bool Ak47::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (have_bullets() && timer.can_shoot()) {
        reduce_bullets();
        timer.start();
        auto calculate_damage_func = [this](float distance) {
            return this->calculate_damage(distance);
        };
        for (int i = 0; i < specs.fire_rate; i++) {
            // aproximadamente se duerme 0.1seg
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            ISpawneableZone::collider_solicitude_t wanted = {specs.width, specs.distance, direction,
                                                             calculate_damage_func};
            spawn.spawn_collider(id, wanted);
        }
    }
    return true;
}

bool Ak47::is_droppable() { return true; }

uint8_t Ak47::calculate_damage(float distance) { return specs.damage * distance; }


bool M3::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (have_bullets() && timer.can_shoot()) {
        reduce_bullets();
        timer.start();
        auto calculate_damage_func = [this](float distance) {
            return this->calculate_damage(distance);
        };
        ISpawneableZone::collider_solicitude_t wanted = {specs.width, specs.distance, direction,
                                                         calculate_damage_func};
        spawn.spawn_collider(id, wanted);
    }
    return true;
}
bool M3::is_droppable() { return true; }

uint8_t M3::calculate_damage(float distance) { return specs.damage / distance; }
bool AWP::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (have_bullets() && timer.can_shoot()) {
        reduce_bullets();
        timer.start();
        auto calculate_damage_func = [this](float distance) {
            return this->calculate_damage(distance);
        };
        ISpawneableZone::collider_solicitude_t wanted = {specs.width, specs.distance, direction,
                                                         calculate_damage_func};
        spawn.spawn_collider(id, wanted);
    }
    return true;
}
bool AWP::is_droppable() { return true; }

uint8_t AWP::calculate_damage([[maybe_unused]] float distance) { return specs.damage; }
bool FireableWeapon::have_bullets() { return specs.current_b != 0; }
void FireableWeapon::reduce_bullets() {
    uint8_t bullets_fired = std::min(specs.current_b, specs.fire_rate);
    specs.current_b -= bullets_fired;
}
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
/* KNIFE */
bool Knife::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    auto function_damage = [this]([[maybe_unused]] float distance) { return specs.damage; };
    ISpawneableZone::collider_solicitude_t wanted = {specs.width, specs.distance, direction,
                                                     function_damage};

    spawn.spawn_collider(id, wanted);
    return true;
}

void Knife::reload() { return; }
WeaponImage Knife::get_weapon_image() { return WeaponImage(code, 0, 0, 0); }

bool Knife::is_droppable() { return false; }
