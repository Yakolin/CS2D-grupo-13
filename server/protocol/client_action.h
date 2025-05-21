#ifndef CLIENT_ACTION_H
#define CLIENT_ACTION_H

#include <cstdint>

#include "../../common/client_common_action.h"
#include "../../common/lobby_types.h"
#include "../../common/player_types.h"
#include "../../common/utility.h"
#include "../game.h"
#include "../interfaces/interface_games_monitor.h"

class ClientAction {
protected:
    player_id_t player_id;

public:
    ClientAction(player_id_t player_id): player_id(player_id) {}
    virtual ~ClientAction() {}
};

namespace ServerSpace {


/*
        MOVEMENT ACTIONS
        */

class Move: public ClientAction, public InterfacePlayerAction, public MoveCommon {

public:
    Move(player_id_t player_id, MoveType move_type);
    ~Move();
    void action(InterfaceGameManager& game) override;
};

/*
        WEAPON ACTIONS
*/

class BuyWeapon: public ClientAction, public InterfacePlayerAction, public BuyWeaponCommon {

public:
    BuyWeapon(player_id_t player_id,
              WeaponCode weapon_code);  // considerando que el arma viene con
    // municion por default
    ~BuyWeapon();
    void action(InterfaceGameManager& game) override;
};

class BuyAmmo: public ClientAction, public InterfacePlayerAction, public BuyAmmoCommon {

public:
    BuyAmmo(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count);
    ~BuyAmmo();
    void action(InterfaceGameManager& game) override;
};

class Reload: public ClientAction, public InterfacePlayerAction {

public:
    Reload(player_id_t player_id);
    ~Reload();
    void action(InterfaceGameManager& game) override;
};

class Shoot: public ClientAction, public InterfacePlayerAction, public ShootCommon {

public:
    Shoot(player_id_t player_id, Position position, ammo_t ammo_count);
    ~Shoot();
    void action(InterfaceGameManager& game) override;
};

/*
        BOMB ACTIONS
*/

class PlantBomb: public ClientAction, public InterfacePlayerAction {
public:
    PlantBomb(player_id_t player_id);
    ~PlantBomb();
    void action(InterfaceGameManager& game) override;
};


class DefuseBomb: public ClientAction, public InterfacePlayerAction {
public:
    DefuseBomb(player_id_t player_id);
    ~DefuseBomb();
    void action(InterfaceGameManager& game) override;
};

/*
GAME ACTIONS
*/

class Drop: public ClientAction, public InterfacePlayerAction {
public:
    Drop(player_id_t player_id);
    ~Drop();
    void action(InterfaceGameManager& game) override;
};

class Equip: public ClientAction, public InterfacePlayerAction, public EquipCommon {
public:
    Equip(player_id_t player_id, EquipType equip_type);
    ~Equip();
    void action(InterfaceGameManager& game) override;
};

}  // namespace ServerSpace
#endif  // !CLIENT_ACTION_H