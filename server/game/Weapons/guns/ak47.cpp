#include "ak47.h"


Ak47::Ak47():
        Weapon(WeaponConfig::get_instance()["weapon"]["ak47"]["damage"].as<damage_t>,
               std::make_unique<Automatic>()),
        FireableWeapon(WeaponConfig::get_instance()["weapon"]["ak47"]["max_bullets"].as<bullet_t>,
                       WeaponConfig::get_instance()["weapon"]["ak47"]["magazine"].as<magazine_t>,
                       WeaponConfig::get_instance()["weapon"]["ak47"]["fire_rate"].as<fire_rate_t>),
        bullets_in_burst(0),
        max_burst(WeaponConfig::get_instance()["weapon"]["ak47"]["max_burst"].as<max_burst_t>),
        time_between_shoots(WeaponConfig::get_instance()["weapon"]["ak47"]["time_between_shoots"]
                                    .as<time_between_shoots_t>),
        burst_coldown(WeaponConfig::get_instance()["weapon"]["ak47"]["burst_coldown"]
                              .as<burst_coldown_t>) {}

Ak47::~Ak47() {}

bool Ak47::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    return false;

    if (bullets_in_burst == 0 && !burst_timer.elapsed(this->burst_coldown))
        return false;

    if (!shot_timer.elapsed(this->time_between_shoots))
        return false;

    if (reduce_bulets()) {
        shot_timer.start();

        auto calculate_damage_func = [this](float distance) {
            return this->calculate_damage(distance);
        };

        ISpawneableZone::collider_solicitude_t wanted = {specs.width, specs.distance, direction,
                                                         calculate_damage_func};
        spawn.spawn_collider(id, wanted);

        bullets_in_burst++;

        if (bullets_in_burst >= this->max_burst) {
            bullets_in_burst = 0;
            burst_timer.start();
        }

        return true;
    }
    return false;
}

bool Ak47::is_droppable() { return true; }

damage_t Ak47::calculate_damage(float distance) { return (this->damage * distance); }
