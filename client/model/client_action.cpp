#include "client_action.h"

using ClientSpace::BuyAmmo;
using ClientSpace::BuyWeapon;
using ClientSpace::CreateGame;
using ClientSpace::DefuseBomb;
using ClientSpace::Drop;
using ClientSpace::Equip;
using ClientSpace::JoinGame;
using ClientSpace::ListGames;
using ClientSpace::MousePosition;
using ClientSpace::Move;
using ClientSpace::PlantBomb;
using ClientSpace::Reload;
using ClientSpace::Shoot;

CreateGame::CreateGame(const std::string& game_name):
        CreateGameCommon(game_name), InterfaceClientAction() {}

CreateGame::~CreateGame() {}

void CreateGame::action(ClientProtocol& protocol) { protocol.send_create_game(this->game_name); }


JoinGame::JoinGame(const std::string& game_name):
        JoinGameCommon(game_name), InterfaceClientAction() {}

JoinGame::~JoinGame() {}

void JoinGame::action(ClientProtocol& protocol) { protocol.send_join_game(this->game_name); }


ListGames::ListGames() {}

ListGames::~ListGames() {}

void ListGames::action(ClientProtocol& protocol) { protocol.send_list_games(); }


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