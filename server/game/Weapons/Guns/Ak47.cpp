#include "Ak47.h"


Ak47::Ak47(GameConfig::weapon_config_t specs):
        FireableWeapon(WeaponCode::AK47, std::make_unique<Automatic>(3, 0.4, 1.8), specs) {}

Ak47::~Ak47() {}

bool Ak47::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    // ACA NO HAY LOGICA DE TIMER
    if (bullets_in_burst == 0 && !burst_timer.elapsed(this->burst_coldown))
        return false;

    if (!shot_timer.elapsed(this->time_between_shoots))
        return false;

    if (!have_bullets())
        return false;
    reduce_bullets();
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

bool Ak47::is_droppable() { return true; }

uint8_t Ak47::calculate_damage(float distance) { return specs.damage * distance; }
