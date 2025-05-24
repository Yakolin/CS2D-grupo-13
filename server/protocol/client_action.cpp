#include "client_action.h"
/*
using ServerSpace::BuyAmmo;
using ServerSpace::BuyWeapon;
using ServerSpace::DefuseBomb;
using ServerSpace::Drop;
using ServerSpace::Equip;
using ServerSpace::PlantBomb;
using ServerSpace::Shoot;
*/
using ServerSpace::Move;
using ServerSpace::Reload;


/*
    MOVEMENT ACTIONS
*/

Move::Move(player_id_t player_id, MoveType move_type):
        ClientAction(player_id), MoveCommon(move_type) {}

Move::~Move() {}

void Move::action_to(IPlayerAction& player) { player.move(this->move_type); }
/*

    WEAPON ACTIONS
    
    BuyWeapon::BuyWeapon(player_id_t player_id, WeaponCode weapon_code):
    ClientAction(player_id), BuyWeaponCommon(weapon_code) {}
    
    BuyWeapon::~BuyWeapon() {}
    
    void BuyWeapon::action_to(IPlayerAction& player) { player.buy_weapon(this->weapon_code); }
    
    
    BuyAmmo::BuyAmmo(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count):
    ClientAction(player_id), BuyAmmoCommon(weapon_type, ammo_count) {}
    
    BuyAmmo::~BuyAmmo() {}
    
    void BuyAmmo::action_to(IPlayerAction& player) {
        player.buy_ammo(this->weapon_type, this->ammo_count);
}
*/


Reload::Reload(player_id_t player_id): ClientAction(player_id) {}

Reload::~Reload() {}

void Reload::action_to(IPlayerAction& player) { player.reload(); }


/*
Shoot::Shoot(player_id_t player_id, coordinate_t mouse_x, coordinate_t mouse_y):

void Shoot::action_to(IPlayerAction& player) { player.shoot(this->mouse_x, this->mouse_y); }
        ClientAction(player_id), ShootCommon(mouse_x, mouse_y) {}

Shoot::~Shoot() {}


    BOMB ACTIONS
    
    PlantBomb::PlantBomb(player_id_t player_id): ClientAction(player_id) {}
    
    PlantBomb::~PlantBomb() {}
    
    void PlantBomb::action_to(IPlayerAction& player) { player.plant_bomb(); }
    
    
    DefuseBomb::DefuseBomb(player_id_t player_id): ClientAction(player_id) {}
    
    DefuseBomb::~DefuseBomb() {}
    
    void DefuseBomb::action_to(IPlayerAction& player) { player.defuse_bomb(); }
    
*/
/*
    GAME ACTIONS
    
    Drop::Drop(player_id_t player_id): ClientAction(player_id) {}
    
    Drop::~Drop() {}
    
    void Drop::action_to(IPlayerAction& player) { player.drop(); }
    
    
    Equip::Equip(player_id_t player_id, EquipType equip_type):
    ClientAction(player_id), EquipCommon(equip_type) {}
    
    Equip::~Equip() {}
    
    void Equip::action_to(IPlayerAction& player) { player.equip(this->equip_type); }
*/