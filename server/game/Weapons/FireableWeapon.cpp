#include "FireableWeapon.h"

FireableWeapon::FireableWeapon(bullet_t max_bullets, magazine_t max_magazine,
                               fire_rate_t fire_rate):
        max_bullets(max_bullets),
        max_magazine(max_magazine),
        fire_rate(fire_rate),
        actual_magazine(max_magazine),
        actual_bullets(max_bullets) {}

FireableWeapon::~FireableWeapon() {}

void FireableWeapon::reload() {
    if (this->actual_bullets < this->max_bullets && this->actual_magazine > 0) {
        bullet_t needed_bullets = this->max_bullets - this->actual_bullets;
        bullet_t bullets_to_reload = std::min(needed_bullets, this->actual_magazine);
        this->actual_bullets += bullets_to_reload;
        this->actual_magazine -= bullets_to_reload;
    }
}

bool FireableWeapon::reduce_bullets() {
    if (this->actual_bullets == 0)
        return false;
    bullet_t bullets_fired = std::min(this->actual_bullets, this->fire_rate);
    this->actual_bullets -= bullets_fired;
    return true;
}

void FireableWeapon::restore_bullets() {
    this->actual_bullets = this->max_bullets;
    this->actual_magazine = this->max_magazine;
}