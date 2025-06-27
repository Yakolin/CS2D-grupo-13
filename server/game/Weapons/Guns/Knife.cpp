#include "Knife.h"

Knife::Knife(GameConfig::weapon_config_t specs):
        Weapon(WeaponCode::KNIFE, specs.damage, specs.distance, specs.width, specs.chance_hit,
               std::make_unique<SemiAutomatic>(static_cast<timer_fire_t>(specs.timer_fire))) {}

Knife::~Knife() {}

damage_t Knife::calculate_damage(float distance [[maybe_unused]]) { return Weapon::damage; }

bool Knife::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (this->fire_mode->can_fire()) {
        WeaponCode weapon_code = this->get_weapon_code();
        ISpawneableZone::collider_solicitude_t wanted = {
                Weapon::width,      Weapon::range,
                Weapon::chance_hit, weapon_code,
                direction,          [this](float value) { return this->calculate_damage(value); }};

        spawn.spawn_collider(id, wanted);
        return true;
    }
    return false;
}

bool Knife::shoot_burst(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (this->fire_mode->can_fire_burst()) {
        WeaponCode weapon_code = this->get_weapon_code();
        ISpawneableZone::collider_solicitude_t wanted = {
                Weapon::width,      Weapon::range,
                Weapon::chance_hit, weapon_code,
                direction,          [this](float value) { return this->calculate_damage(value); }};

        spawn.spawn_collider(id, wanted);
        return true;
    }
    return false;
}

bool Knife::reload() { return false; };

bool Knife::have_bullets() { return true; }

WeaponImage Knife::get_weapon_image() { return WeaponImage(code, 0, 0); }

bool Knife::is_droppable() { return false; }
