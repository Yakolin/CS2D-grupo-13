#include "FireableWeapon.h"

FireableWeapon::FireableWeapon(WeaponCode weapon_code, damage_t damage, range_t range,
                               width_t width, std::unique_ptr<FireMode>&& fire_mode,
                               bullet_t max_bullets, magazine_t max_magazine):
        Weapon(weapon_code, damage, range, width, std::move(fire_mode)),
        max_bullets(max_bullets),
        max_magazine(max_magazine),
        actual_bullets(max_bullets),
        actual_magazine(max_magazine) {}

FireableWeapon::~FireableWeapon() {}

void FireableWeapon::reduce_bullets() {
    if (this->actual_bullets > 0) {
        this->actual_bullets--;
    }
}

void FireableWeapon::restart() {
    this->actual_bullets = this->max_bullets;
    this->actual_magazine = this->max_magazine;
}

void FireableWeapon::shoot_common(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    ISpawneableZone::collider_solicitude_t wanted = {Weapon::width, Weapon::range, direction,
                                                     [this]() {
                                                         return this->calculate_damage();
                                                     }};  // esto deberia ser darle el daño y listo
    spawn.spawn_collider(id, wanted);
    this->reduce_bullets();
}

bool FireableWeapon::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (this->actual_bullets > 0) {
        if (this->fire_mode->can_fire()) {  // esto DEBE disparar solo una bala
            this->shoot_common(spawn, id, direction);
            return true;
        }
    }
    return false;
}

bool FireableWeapon::shoot_burst(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (this->actual_bullets > 0) {
        if (this->fire_mode->can_fire_burst()) {
            this->shoot_common(spawn, id, direction);
            return true;
        }
    }
    return false;
}

void FireableWeapon::reload() {
    if (actual_bullets > 0 && actual_magazine < max_magazine) {
        magazine_t needed_bullets = max_magazine - actual_magazine;
        magazine_t available_bullets = std::min(needed_bullets, actual_bullets);
        actual_magazine += available_bullets;
        actual_bullets -= available_bullets;
    }
}

WeaponImage FireableWeapon::get_weapon_image() {
    return WeaponImage(Weapon::get_weapon_code(), this->actual_bullets, this->actual_magazine);
}