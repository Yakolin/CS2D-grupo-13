#include "Knife.h"

Knife::Knife(GameConfig::weapon_config_t specs):
        Weapon(WeaponCode::KNIFE, specs.damage, specs.distance, specs.width,
               std::make_unique<SemiAutomatic>(static_cast<fire_rate_t>(specs.fire_rate))) {}

Knife::~Knife() {}

damage_t Knife::calculate_damage() { return Weapon::damage; }

bool Knife::set_on_action(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (this->fire_mode->can_fire()) {
        ISpawneableZone::collider_solicitude_t wanted = {
                this->width, this->range, direction, [this]() { return this->calculate_damage(); }};

        spawn.spawn_collider(id, wanted);
        return true;
    }
    return false;
}

bool Knife::shoot_burst(ISpawneableZone& spawn, player_id_t id, Position& direction) {
    if (this->fire_mode->can_fire_burst()) {
        ISpawneableZone::collider_solicitude_t wanted = {
                this->width, this->range, direction, [this]() { return this->calculate_damage(); }};

        spawn.spawn_collider(id, wanted);
        return true;
    }
    return false;
}

void Knife::reload() {};

WeaponImage Knife::get_weapon_image() { return WeaponImage(code, 0, 0); }

bool Knife::is_droppable() { return false; }
