#include "client_action.h"
/*
using ServerSpace::BuyAmmo;
using ServerSpace::PlantBomb;
*/
using ServerSpace::BuyWeapon;
using ServerSpace::DefuseBomb;
using ServerSpace::Drop;
using ServerSpace::Equip;
using ServerSpace::MousePosition;
using ServerSpace::Move;
using ServerSpace::Reload;
using ServerSpace::Shoot;
using ServerSpace::ShootBurst;


/*
    MOVEMENT ACTIONS
*/

Move::Move(const player_id_t& player_id, const MoveType& move_type):
        ClientAction(player_id), MoveCommon(move_type) {}

Move::~Move() {}

void Move::action_to(IPlayerAction& player) { player.move(this->move_type); }


BuyWeapon::BuyWeapon(const player_id_t& player_id, const WeaponCode& weapon_code):
        ClientAction(player_id), BuyWeaponCommon(weapon_code) {}

BuyWeapon::~BuyWeapon() {}

void BuyWeapon::action_to(IPlayerAction& player) { player.buy_weapon(this->weapon_code); }


/*

    WEAPON ACTIONS


    BuyAmmo::BuyAmmo(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count):
    ClientAction(player_id), BuyAmmoCommon(weapon_type, ammo_count) {}

BuyAmmo::~BuyAmmo() {}

void BuyAmmo::action_to(IPlayerAction& player) {
    player.buy_ammo(this->weapon_type, this-ammo_count);
}

*/


Reload::Reload(const player_id_t& player_id): ClientAction(player_id) {}

Reload::~Reload() {}

void Reload::action_to(IPlayerAction& player) { player.reload(); }


Shoot::Shoot(const player_id_t& player_id, const coordinate_t& mouse_x,
             const coordinate_t& mouse_y):
        ClientAction(player_id), ShootCommon(mouse_x, mouse_y) {}

Shoot::~Shoot() {}

void Shoot::action_to(IPlayerAction& player) { player.shoot(this->mouse_x, this->mouse_y); }


ShootBurst::ShootBurst(const player_id_t& player_id, const coordinate_t& mouse_x,
                       const coordinate_t& mouse_y):
        ClientAction(player_id), ShootCommon(mouse_x, mouse_y) {}

ShootBurst::~ShootBurst() {}

void ShootBurst::action_to(IPlayerAction& player) {
    player.shoot_burst(this->mouse_x, this->mouse_y);
}


Drop::Drop(const player_id_t& player_id): ClientAction(player_id) {}

Drop::~Drop() {}

void Drop::action_to(IPlayerAction& player) { player.drop(); }


Equip::Equip(const player_id_t& player_id, const EquipType& equip_type):
        ClientAction(player_id), EquipCommon(equip_type) {}

Equip::~Equip() {}

void Equip::action_to(IPlayerAction& player) { player.change_weapon(this->equip_type); }

/*


    BOMB ACTIONS

    PlantBomb::PlantBomb(player_id_t player_id): ClientAction(player_id) {}

    PlantBomb::~PlantBomb() {}

    void PlantBomb::action_to(IPlayerAction& player) { player.plant_bomb(); }

*/

DefuseBomb::DefuseBomb(const player_id_t& player_id): ClientAction(player_id) {}

DefuseBomb::~DefuseBomb() {}

void DefuseBomb::action_to(IPlayerAction& player) { player.defuse_bomb(); }

/*
GAME ACTIONS


*/
MousePosition::MousePosition(const player_id_t& player_id, const coordinate_t& mouse_x,
                             const coordinate_t& mouse_y):
        ClientAction(player_id), MousePositionCommon(mouse_x, mouse_y) {}
MousePosition::~MousePosition() {}
void MousePosition::action_to(IPlayerAction& player) { player.watch(this->mouse_x, this->mouse_y); }
