#ifndef CLIENT_ACTION_H
#define CLIENT_ACTION_H

#include "../../common/client_common_action.h"

#include "protocol.h"

class InterfaceClientAction {
public:
    InterfaceClientAction() = default;
    virtual ~InterfaceClientAction() = default;
    virtual void action(ClientProtocol& protocol) = 0;
};

/*
    LOBBY ACTIONS
*/

namespace Client {

class CreateGame: public CreateGameCommon, public InterfaceClientAction {
public:
    CreateGame(const std::string& game_name);
    ~CreateGame();
    void action(ClientProtocol& protocol) override;
};

class JoinGame: public JoinGameCommon, public InterfaceClientAction {
public:
    JoinGame(const std::string& game_name);
    ~JoinGame();
    void action(ClientProtocol& protocol) override;
};

class ListGames: public InterfaceClientAction {
public:
    ListGames();
    ~ListGames();
    void action(ClientProtocol& protocol) override;
};

/*
    PLAYER ACTIONS
    */

class Move: public MoveCommon, public InterfaceClientAction {
public:
    Move(MoveType move_type);
    ~Move();
    void action(ClientProtocol& protocol) override;
};

class BuyWeapon: public BuyWeaponCommon, public InterfaceClientAction {
public:
    BuyWeapon(WeaponCode weapon_code);
    ~BuyWeapon();
    void action(ClientProtocol& protocol) override;
};

class BuyAmmo: public BuyAmmoCommon, public InterfaceClientAction {
public:
    BuyAmmo(WeaponType weapon_type, ammo_t ammo_count);
    ~BuyAmmo();
    void action(ClientProtocol& protocol) override;
};

class Reload: public InterfaceClientAction {
public:
    Reload(WeaponType weapon_type);
    ~Reload();
    void action(ClientProtocol& protocol) override;
};

class Shoot: public InterfaceClientAction {
public:
    Shoot(WeaponType weapon_type, ammo_t ammo_count);
    ~Shoot();
    void action(ClientProtocol& protocol) override;
};

class DropWeapon: public InterfaceClientAction {
public:
    DropWeapon(WeaponType weapon_type);
    ~DropWeapon();
    void action(ClientProtocol& protocol) override;
};

class PlantBomb: public InterfaceClientAction {
public:
    PlantBomb();
    ~PlantBomb();
    void action(ClientProtocol& protocol) override;
};

class DefuseBomb: public InterfaceClientAction {
public:
    DefuseBomb();
    ~DefuseBomb();
    void action(ClientProtocol& protocol) override;
};

class DropBomb: public InterfaceClientAction {
public:
    DropBomb();
    ~DropBomb();
    void action(ClientProtocol& protocol) override;
};

}  // namespace Client


#endif