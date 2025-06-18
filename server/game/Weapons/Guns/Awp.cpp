#include "Awp.h"

Awp::Awp(GameConfig::weapon_config_t specs): FireableWeapon(WeaponCode::AWP, specs) {}

Awp::~Awp() {}

bool Awp::is_droppable() { return true; }

uint8_t Awp::calculate_damage([[maybe_unused]] float distance) { return specs.damage; }

bool Awp::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
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