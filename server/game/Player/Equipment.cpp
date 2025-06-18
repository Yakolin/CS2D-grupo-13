#include "Equipment.h"

Equipment::Equipment(const player_id_t& player_id, ISpawneableZone& spawneable_zone,
                     IDroppableZone& droppable_zone):
        player_id(player_id),
        spawneable_zone(spawneable_zone),
        droppable_zone(droppable_zone),
        primary(std::make_shared<NullWeapon>()),
        secondary(std::make_shared<Glock>()),
        knife(std::make_shared<Knife>()),
        weapon_in_hand(this->secondary) {}

Equipment::~Equipment() {}

void Equipment::new_weapon_in_hand(const std::shared_ptr<IInteractuable>& weapon) {
    if (!weapon || weapon->get_weapon_code() == WeaponCode::NONE)
        return;
    this->weapon_in_hand = weapon;
}

void Equipment::change_weapon(const EquipType& equip) {
    switch (equip) {
        case EquipType::KNIFE:
            this->new_weapon_in_hand(this->knife);
            break;
        case EquipType::SECONDARY:
            this->new_weapon_in_hand(this->secondary);
            break;
        case EquipType::PRIMARY:
            this->new_weapon_in_hand(this->primary);
            break;
        case EquipType::BOMB:
            this->new_weapon_in_hand(this->bomb.lock());
        default:
            break;
    }
}
void Equipment::buy_weapon_by_code(const WeaponCode& weapon_code, const money_t money) {
    switch (weapon_code) {
        case WeaponCode::AK47:
            if (money >= WeaponConfig::get_instance()["weapon"]["ak47"]["price"].as<money_t>()) {
                this->primary = std::make_shared<Ak47>();
            }
            break;
        case WeaponCode::M3:
            if (money >= WeaponConfig::get_instance()["weapon"]["m3"]["price"].as<money_t>()) {
                this->primary = std::make_shared<M3>();
            }
            break;
        case WeaponCode::AWP:
            if (money >= WeaponConfig::get_instance()["weapon"]["awp"]["price"].as<money_t>()) {
                this->primary = std::make_shared<Awp>();
            }
            break;
        default:
            break;
    }
}

void Equipment::reset_equipment() {
    this->primary.reset();
    this->secondary.reset();
    bomb.reset();
}

void Equipment::restore() {
    this->primary->restore_bullets();
    this->secondary->restore_bullets();
    // Cuchillo y bomba posiblemente no necesiten esto
}

void Equipment::drop_weapon() {
    if (this->weapon_in_hand) {
        if (this->weapon_in_hand == this->primary) {
            std::shared_ptr<IInteractuable> dropped = this->weapon_in_hand;
            this->droppable_zone.drop(this->player_id, dropped);
            this->new_weapon_in_hand(this->secondary);
            this->primary = std::make_shared<NullWeapon>();
        }
    }
}

void Equipment::reload() { this->weapon_in_hand->reload(); }

void Equipment::shoot(const ShootType& shoot_type, Position& position) {
    if (weapon_in_hand->get_weapon_code() == WeaponCode::BOMB && bomb.lock()) {
        if (weapon_in_hand->set_on_action(this->spawneable_zone, this->player_id, shoot_type,
                                          position)) {
            this->change_weapon(EquipType::SECONDARY);
            bomb.reset();
        }
    } else {
        weapon_in_hand->set_on_action(this->spawneable_zone, this->player_id, shoot_type, position);
    }
}

std::vector<WeaponImage> Equipment::get_weapons_image() {
    std::vector<WeaponImage> weapons;
    weapons.push_back(primary->get_weapon_image());
    weapons.push_back(secondary->get_weapon_image());
    weapons.push_back(knife->get_weapon_image());
    if (bomb.lock())
        weapons.push_back(bomb.lock()->get_weapon_image());
    return weapons;
}
void Equipment::equip_bomb(std::weak_ptr<Bomb> new_bomb) {
    bomb = new_bomb;
    if (bomb.lock())
        bomb.lock()->set_equiped();
}
bool Equipment::equip_droppable(const std::shared_ptr<IInteractuable>& droppable) {
    if (droppable->get_weapon_code() == WeaponCode::BOMB) {
        std::weak_ptr<Bomb> casted_bomb = std::static_pointer_cast<Bomb>(droppable);
        equip_bomb(casted_bomb);
        return true;
    }
    if (!primary->is_droppable()) {
        primary = std::static_pointer_cast<Weapon>(droppable);
        return true;
    }
    return false;
}

void Equipment::drop_all() {
    if (primary->is_droppable()) {
        std::shared_ptr<IInteractuable> dropped = this->primary;
        droppable_zone.drop(player_id, dropped);
        this->primary = std::make_shared<NullWeapon>();
    }
    if (bomb.lock()) {
        std::shared_ptr<IInteractuable> dropped = bomb.lock();
        droppable_zone.drop(player_id, dropped);
        bomb.reset();
    }
}
WeaponCode Equipment::get_equiped_code() { return weapon_in_hand->get_weapon_code(); }
