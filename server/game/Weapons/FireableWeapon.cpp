#include "FireableWeapon.h"

FireableWeapon::FireableWeapon(WeaponCode weapon_code, damage_t damage, range_t range,
                               width_t width, chance_hit_t chance_hit,
                               std::unique_ptr<FireMode>&& fire_mode, bullet_t max_bullets,
                               magazine_t max_magazine):
        Weapon(weapon_code, damage, range, width, chance_hit, std::move(fire_mode)),
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
    WeaponCode weapon_code = this->get_weapon_code();
    ISpawneableZone::collider_solicitude_t wanted = {
            Weapon::width,      Weapon::range,
            Weapon::chance_hit, weapon_code,
            direction,          [this](float value) { return this->calculate_damage(value); }};
    spawn.spawn_collider(id, wanted);
    this->reduce_bullets();
}


bool FireableWeapon::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (this->have_bullets()) {
        if (this->fire_mode->can_fire()) {  // esto DEBE disparar solo una bala
            this->shoot_common(spawn, id, direction);
            return true;
        }
    }
    return false;
}

bool FireableWeapon::shoot_burst(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (this->have_bullets()) {
        if (this->fire_mode->can_fire_burst()) {
            this->shoot_common(spawn, id, direction);
            return true;
        }
    }
    return false;
}

bool FireableWeapon::reload() {
    if (this->actual_magazine > 0 && this->actual_bullets < this->max_bullets) {
        bullet_t needed_bullets = this->max_bullets - this->actual_bullets;
        bullet_t bullets_to_reload = std::min(needed_bullets, this->actual_magazine);

        this->actual_bullets += bullets_to_reload;
        this->actual_magazine -= bullets_to_reload;
        return true;
    }
    return false;
}

bool FireableWeapon::have_bullets() { return this->actual_bullets > 0; }

WeaponImage FireableWeapon::get_weapon_image() {
    return WeaponImage(Weapon::get_weapon_code(), this->actual_bullets, this->actual_magazine);
}
