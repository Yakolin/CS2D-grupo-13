#include "Equipment.h"

Equipment::Equipment(const player_id_t& player_id, ISpawneableZone& spawneable_zone,
                     IDroppableZone& droppable_zone, ISoundZone& sound_zone,
                     WeaponFactory& weapon_factory):
        player_id(player_id),
        spawneable_zone(spawneable_zone),
        droppable_zone(droppable_zone),
        sound_zone(sound_zone),
        weapon_factory(weapon_factory),
        primary(weapon_factory.weapon_create(WeaponCode::NONE)),
        secondary(weapon_factory.weapon_create(WeaponCode::GLOCK)),
        knife(weapon_factory.create_knife()),
        weapon_in_hand(this->secondary) {}

Equipment::~Equipment() {}

void Equipment::new_weapon_in_hand(const std::shared_ptr<IInteractuable>& weapon) {
    if (!weapon || weapon->get_weapon_code() == WeaponCode::NONE || this->weapon_in_hand == weapon)
        return;
    this->weapon_in_hand = weapon;
    sound_zone.want_emit_sound(player_id, std::make_shared<Sound>(SoundType::CHANGE_WEAPON));
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
            return;
    }
}
void Equipment::buy_weapon_by_code(const WeaponCode& weapon_code, money_t& money) {
    money_t price = weapon_factory.price_weapon(weapon_code);
    if (price > money)
        return;
    if (primary->code != WeaponCode::NONE) {
        std::shared_ptr<IInteractuable> dropped = this->primary;
        droppable_zone.drop(player_id, dropped);
    }
    primary = weapon_factory.weapon_create(weapon_code);
    money -= price;
    this->change_weapon(EquipType::PRIMARY);
    sound_zone.want_emit_sound(player_id, std::make_shared<Sound>(SoundType::BUY));
}
void Equipment::reset_equipment() {
    primary = weapon_factory.weapon_create(WeaponCode::NONE);
    secondary = weapon_factory.weapon_create(WeaponCode::NONE);
    secondary = weapon_factory.weapon_create(WeaponCode::GLOCK);
    change_weapon(EquipType::SECONDARY);
    bomb.reset();
}
void Equipment::restore() {
    if (primary->code != WeaponCode::NONE) {
        this->primary->restart();
        change_weapon(EquipType::PRIMARY);
    } else {
        change_weapon(EquipType::SECONDARY);
    }
    this->secondary->restart();
    bomb.reset();
}

void Equipment::drop_weapon() {
    if (this->weapon_in_hand) {
        if (this->weapon_in_hand == this->primary) {
            std::shared_ptr<IInteractuable> dropped = this->weapon_in_hand;
            this->droppable_zone.drop(this->player_id, dropped);
            sound_zone.want_emit_sound(player_id, std::make_shared<Sound>(SoundType::DROP));
            this->new_weapon_in_hand(this->secondary);
            this->primary = std::make_shared<NullWeapon>();
        }
    }
}

void Equipment::reload() {
    if (this->weapon_in_hand->reload()) {
        this->sound_zone.want_emit_sound(this->player_id,
                                         std::make_shared<Sound>(SoundType::RELOAD));
    }
}

void Equipment::shoot(Position& position) {
    if (this->weapon_in_hand->have_bullets()) {
        if (weapon_in_hand->get_weapon_code() == WeaponCode::BOMB && bomb.lock()) {
            if (weapon_in_hand->set_on_action(this->spawneable_zone, this->player_id, position)) {
                this->change_weapon(EquipType::SECONDARY);
                bomb.reset();
            }
        } else {
            weapon_in_hand->set_on_action(this->spawneable_zone, this->player_id, position);
        }
    } else {
        if (this->weapon_in_hand->reload()) {
            this->sound_zone.want_emit_sound(this->player_id,
                                             std::make_shared<Sound>(SoundType::RELOAD));
        }
    }
}

void Equipment::shoot_burst(Position& position) {
    if (weapon_in_hand->get_weapon_code() == WeaponCode::BOMB && bomb.lock()) {
        if (weapon_in_hand->shoot_burst(this->spawneable_zone, this->player_id, position)) {
            this->change_weapon(EquipType::SECONDARY);
            bomb.reset();
        }
    } else {
        weapon_in_hand->shoot_burst(this->spawneable_zone, this->player_id, position);
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
        sound_zone.want_emit_sound(player_id, std::make_shared<Sound>(SoundType::PICK_UP));
        return true;
    }
    if (!primary->is_droppable()) {
        primary = std::static_pointer_cast<FireableWeapon>(droppable);
        sound_zone.want_emit_sound(player_id, std::make_shared<Sound>(SoundType::PICK_UP));
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
    sound_zone.want_emit_sound(player_id, std::make_shared<Sound>(SoundType::DROP));
}
WeaponCode Equipment::get_equiped_code() { return weapon_in_hand->get_weapon_code(); }
