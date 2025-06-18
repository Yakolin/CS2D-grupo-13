#include "M3.h"

M3::M3(GameConfig::weapon_config_t specs): FireableWeapon(WeaponCode::M3, specs) {}

M3::~M3() {}

bool M3::is_droppable() { return true; }

uint8_t M3::calculate_damage(float distance) { return specs.damage / distance; }

bool M3::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (have_bullets() && timer.can_shoot()) {
        timer.start();
        reduce_bullets();
        auto calculate_damage_func = [this](float distance) {
            return this->calculate_damage(distance);
        };
        ISpawneableZone::collider_solicitude_t wanted = {specs.width, specs.distance, this->code,
                                                         direction, calculate_damage_func};
        spawn.spawn_collider(id, wanted);
    }
    return true;
}