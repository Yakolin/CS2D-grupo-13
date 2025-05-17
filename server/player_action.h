#ifndef PLAYER_ACTION_H
#define PLAYER_ACTION_H

#include <cstdint>

#include "../common/client_common_action.h"
#include "../common/lobby_types.h"
#include "../common/player_types.h"

#include "game.h"
#include "games_monitor.h"

class ClientAction {
protected:
    player_id_t player_id;

public:
    ClientAction(player_id_t player_id): player_id(player_id) {}
    virtual ~ClientAction() {}
};

/*
LOBBY ACTIONS
*/
class InterfaceLobbyAction {
public:
    InterfaceLobbyAction() = default;
    virtual ~InterfaceLobbyAction() = default;
    virtual void action(InterfaceGamesMonitor& monitor) = 0;
};

/*
        PLAYER ACTIONS
*/

class InterfacePlayerAction {

public:
    InterfacePlayerAction() = default;
    virtual ~InterfacePlayerAction() = default;
    virtual void action(InterfaceGame& game) = 0;
};

namespace Server {


/*
CREATE GAME
*/

class CreateGame: public ClientAction, public InterfaceLobbyAction, public CreateGameCommon {

public:
    CreateGame(player_id_t player_id, const std::string& game_name);
    ~CreateGame();
    void action(InterfaceGamesMonitor& monitor) override;
};

/*
        JOIN GAME
        */

class JoinGame: public ClientAction, public InterfaceLobbyAction, public JoinGameCommon {

public:
    JoinGame(player_id_t player_id, const std::string& game_name);
    ~JoinGame();
    void action(InterfaceGamesMonitor& monitor) override;
};

/*
        LIST GAMES
*/

class ListGames: public ClientAction, public InterfaceLobbyAction {
public:
    ListGames(player_id_t player_id);
    ~ListGames();
    void action(InterfaceGamesMonitor& monitor) override;
};


/*
        MOVEMENT ACTIONS
        */

class Move: public ClientAction, public InterfacePlayerAction, public MoveCommon {

public:
    Move(player_id_t player_id, MoveType move_type);
    ~Move();
    void action(InterfaceGame& game) override;
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
    void action(InterfaceGame& game) override;
};

class BuyAmmo: public ClientAction, public InterfacePlayerAction, public BuyAmmoCommon {

public:
    BuyAmmo(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count);
    ~BuyAmmo();
    void action(InterfaceGame& game) override;
};

class Reload: public ClientAction, public InterfacePlayerAction, public ReloadCommon {

public:
    Reload(player_id_t player_id, WeaponType weapon_type);
    ~Reload();
    void action(InterfaceGame& game) override;
};

class Shoot: public ClientAction, public InterfacePlayerAction, public ShootCommon {

public:
    Shoot(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count);
    ~Shoot();
    void action(InterfaceGame& game) override;
};

class DropWeapon: public ClientAction, public InterfacePlayerAction, public DropWeaponCommon {

public:
    DropWeapon(player_id_t player_id, WeaponType weapon_type);
    ~DropWeapon();
    void action(InterfaceGame& game) override;
};

/*
BOMB ACTIONS
*/

class PlantBomb: public ClientAction, public InterfacePlayerAction {
public:
    PlantBomb(player_id_t player_id);
    ~PlantBomb();
    void action(InterfaceGame& game) override;
};

class DropBomb: public ClientAction, public InterfacePlayerAction {
public:
    DropBomb(player_id_t player_id);
    ~DropBomb();
    void action(InterfaceGame& game) override;
};

class DefuseBomb: public ClientAction, public InterfacePlayerAction {
public:
    DefuseBomb(player_id_t player_id);
    ~DefuseBomb();
    void action(InterfaceGame& game) override;
};

}  // namespace Server
#endif  // !PLAYER_ACTION_H
