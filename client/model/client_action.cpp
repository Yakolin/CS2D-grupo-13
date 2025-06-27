#include "client_action.h"

using ClientSpace::BuyAmmo;
using ClientSpace::BuyWeapon;
using ClientSpace::DefuseBomb;
using ClientSpace::Drop;
using ClientSpace::Equip;
using ClientSpace::MousePosition;
using ClientSpace::Move;
using ClientSpace::PlantBomb;
using ClientSpace::Reload;
using ClientSpace::Shoot;
using ClientSpace::ShootBurst;


Move::Move(MoveType& move_type): MoveCommon(move_type), InterfaceClientAction() {}

Move::~Move() {}

void Move::action(ClientProtocol& protocol) { protocol.send_move(this->move_type); }


BuyWeapon::BuyWeapon(WeaponCode& weapon_code):
        BuyWeaponCommon(weapon_code), InterfaceClientAction() {}

BuyWeapon::~BuyWeapon() {}

void BuyWeapon::action(ClientProtocol& protocol) { protocol.send_buy_weapon(this->weapon_code); }


BuyAmmo::BuyAmmo(WeaponType& weapon_type, ammo_t& ammo_count):
        BuyAmmoCommon(weapon_type, ammo_count), InterfaceClientAction() {}

BuyAmmo::~BuyAmmo() {}

void BuyAmmo::action(ClientProtocol& protocol) {
    protocol.send_buy_ammo(this->weapon_type, this->ammo_count);
}

Reload::Reload(): InterfaceClientAction() {}

Reload::~Reload() {}

void Reload::action(ClientProtocol& protocol) { protocol.send_reload(); }


Shoot::Shoot(coordinate_t& mouse_x, coordinate_t& mouse_y):
        ShootCommon(mouse_x, mouse_y), InterfaceClientAction() {}

Shoot::~Shoot() {}

void Shoot::action(ClientProtocol& protocol) { protocol.send_shoot(this->mouse_x, this->mouse_y); }


ShootBurst::ShootBurst(coordinate_t& mouse_x, coordinate_t& mouse_y):
        ShootCommon(mouse_x, mouse_y), InterfaceClientAction() {}

ShootBurst::~ShootBurst() {}

void ShootBurst::action(ClientProtocol& protocol) {
    protocol.send_shoot_burst(this->mouse_x, this->mouse_y);
}


PlantBomb::PlantBomb(): InterfaceClientAction() {}

PlantBomb::~PlantBomb() {}

void PlantBomb::action(ClientProtocol& protocol) { protocol.send_plant_bomb(); }


DefuseBomb::DefuseBomb(): InterfaceClientAction() {}

DefuseBomb::~DefuseBomb() {}

void DefuseBomb::action(ClientProtocol& protocol) { protocol.send_defuse_bomb(); }


Drop::Drop(): InterfaceClientAction() {}

Drop::~Drop() {}

void Drop::action(ClientProtocol& protocol) { protocol.send_drop(); }


Equip::Equip(EquipType& equip_type): EquipCommon(equip_type), InterfaceClientAction() {}

Equip::~Equip() {}

void Equip::action(ClientProtocol& protoocol) { protoocol.send_equip(this->equip_type); }


MousePosition::MousePosition(coordinate_t& mouse_x, coordinate_t& mouse_y):
        MousePositionCommon(mouse_x, mouse_y), InterfaceClientAction() {}

MousePosition::~MousePosition() {}

void MousePosition::action(ClientProtocol& protocol) {
    protocol.send_mouse_position(this->mouse_x, this->mouse_y);
}
