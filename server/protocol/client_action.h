#ifndef CLIENT_ACTION_H
#define CLIENT_ACTION_H

#include <cstdint>

#include "../../common/client_common_action.h"
#include "../../common/game_image.h"
#include "../../common/lobby_types.h"
#include "../../common/player_command_types.h"
#include "../interfaces/interface_player_action.h"

class ClientAction {
protected:
    player_id_t player_id;
    explicit ClientAction(const player_id_t& player_id): player_id(player_id) {}

public:
    player_id_t get_player_id() { return this->player_id; }
    virtual void action_to(IPlayerAction& player) = 0;

    virtual ~ClientAction() {}
};

namespace ServerSpace {

/*
    MOVEMENT ACTIONS
*/

class Move: public ClientAction, public MoveCommon {

public:
    Move(const player_id_t& player_id, const MoveType& move_type);
    ~Move();
    void action_to(IPlayerAction& player) override;
};

class BuyWeapon: public ClientAction, public BuyWeaponCommon {
public:
    BuyWeapon(const player_id_t& player_id,
              const WeaponCode& weapon_code);  // considerando que el arma viene con
    // municion por default
    ~BuyWeapon();
    void action_to(IPlayerAction& player) override;
};
/*

WEAPON ACTIONS


class BuyAmmo: public ClientAction, public BuyAmmoCommon {

public:
BuyAmmo(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count);
~BuyAmmo();
void action_to(IPlayerAction& player) override;
};

*/


class Reload: public ClientAction {

public:
    explicit Reload(const player_id_t& player_id);
    ~Reload();
    void action_to(IPlayerAction& player) override;
};
class Shoot: public ClientAction, public ShootCommon {
public:
    Shoot(const player_id_t& player_id, const coordinate_t& mouse_x, const coordinate_t& mouse_y);
    ~Shoot();
    void action_to(IPlayerAction& player) override;
};

class ShootBurst: public ClientAction, public ShootCommon {
public:
    ShootBurst(const player_id_t& player_id, const coordinate_t& mouse_x,
               const coordinate_t& mouse_y);
    ~ShootBurst();
    void action_to(IPlayerAction& player) override;
};

class DefuseBomb: public ClientAction {
public:
    explicit DefuseBomb(const player_id_t& player_id);
    ~DefuseBomb();
    void action_to(IPlayerAction& player) override;
};


class Drop: public ClientAction {
public:
    explicit Drop(const player_id_t& player_id);
    ~Drop();
    void action_to(IPlayerAction& player) override;
};

class Equip: public ClientAction, public EquipCommon {
public:
    Equip(const player_id_t& player_id, const EquipType& equip_type);
    ~Equip();
    void action_to(IPlayerAction& player) override;
};

/*
    GAME ACTIONS
    */


class MousePosition: public ClientAction, public MousePositionCommon {
public:
    MousePosition(const player_id_t& player_id, const coordinate_t& mouse_x,
                  const coordinate_t& mouse_y);
    ~MousePosition();
    void action_to(IPlayerAction& player) override;
};

}  // namespace ServerSpace
#endif  // !CLIENT_ACTION_H
