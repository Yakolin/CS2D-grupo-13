#ifndef PLAYER_ACTION_H
#define PLAYER_ACTION_H

#include <cstdint>

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
class LobbyAction {
public:
    LobbyAction() = default;
    virtual ~LobbyAction() = default;
    virtual void action(InterfaceGamesMonitor& monitor) = 0;
};

/*
        CREATE GAME
*/

class CreateGame: public LobbyAction, public ClientAction {
private:
    const std::string game_name;

public:
    CreateGame(player_id_t player_id, const std::string& game_name);
    ~CreateGame();
    void action(InterfaceGamesMonitor& monitor) override;
};

/*
        JOIN GAME
*/

class JoinGame: public LobbyAction, public ClientAction {
private:
    const std::string game_name;

public:
    JoinGame(player_id_t player_id, const std::string& game_name);
    ~JoinGame();
    void action(InterfaceGamesMonitor& monitor) override;
};

/*
        LIST GAMES
*/

class ListGames: public LobbyAction, public ClientAction {
public:
    ListGames(player_id_t player_id);
    ~ListGames();
    void action(InterfaceGamesMonitor& monitor) override;
};


/*
        PLAYER ACTIONS
*/

class PlayerAction {

public:
    PlayerAction() = default;
    virtual ~PlayerAction() = default;
    virtual void action(InterfaceGame& game) = 0;
};

/*
        MOVEMENT ACTIONS
*/

class Move: public PlayerAction, public ClientAction {
private:
    MoveType move_type;

public:
    Move(player_id_t player_id, MoveType move_type);
    ~Move();
    void action(InterfaceGame& game) override;
};

/*
        WEAPON ACTIONS
*/

class BuyWeapon: public PlayerAction, public ClientAction {
private:
    WeaponCode weapon_code;

public:
    BuyWeapon(player_id_t player_id,
              WeaponCode weapon_code);  // considerando que el arma viene con
                                        // municion por default
    ~BuyWeapon();
    void action(InterfaceGame& game) override;
};

class BuyAmmo: public PlayerAction, public ClientAction {
private:
    WeaponType weapon_type;
    ammo_t ammo_count;

public:
    BuyAmmo(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count);
    ~BuyAmmo();
    void action(InterfaceGame& game) override;
};

class Reload: public PlayerAction, public ClientAction {
private:
    WeaponType weapon_type;

public:
    Reload(player_id_t player_id, WeaponType weapon_type);
    ~Reload();
    void action(InterfaceGame& game) override;
};

class Shoot: public PlayerAction, public ClientAction {
private:
    WeaponType weapon_type;
    ammo_t ammo_count;

public:
    Shoot(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count);
    ~Shoot();
    void action(InterfaceGame& game) override;
};

class DropWeapon: public PlayerAction, public ClientAction {
private:
    WeaponType weapon_type;

public:
    DropWeapon(player_id_t player_id, WeaponType weapon_type);
    ~DropWeapon();
    void action(InterfaceGame& game) override;
};

/*
        BOMB ACTIONS
*/

class PlantBomb: public PlayerAction, public ClientAction {
public:
    PlantBomb(player_id_t player_id);
    ~PlantBomb();
    void action(InterfaceGame& game) override;
};

class DropBomb: public PlayerAction, public ClientAction {
public:
    DropBomb(player_id_t player_id);
    ~DropBomb();
    void action(InterfaceGame& game) override;
};

class DefuseBomb: public PlayerAction, public ClientAction {
public:
    DefuseBomb(player_id_t player_id);
    ~DefuseBomb();
    void action(InterfaceGame& game) override;
};

#endif  // !PLAYER_ACTION_H
