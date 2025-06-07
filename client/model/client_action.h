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
    PLAYER ACTIONS
*/

namespace ClientSpace {

class Move: public MoveCommon, public InterfaceClientAction {
public:
    Move(MoveType& move_type);
    ~Move();
    void action(ClientProtocol& protocol) override;
};

class BuyWeapon: public BuyWeaponCommon, public InterfaceClientAction {
public:
    BuyWeapon(WeaponCode& weapon_code);
    ~BuyWeapon();
    void action(ClientProtocol& protocol) override;
};

class BuyAmmo: public BuyAmmoCommon, public InterfaceClientAction {
public:
    BuyAmmo(WeaponType& weapon_type, ammo_t& ammo_count);
    ~BuyAmmo();
    void action(ClientProtocol& protocol) override;
};

class Reload: public InterfaceClientAction {
public:
    Reload();
    ~Reload();
    void action(ClientProtocol& protocol) override;
};

class Shoot: public ShootCommon, public InterfaceClientAction {
public:
    Shoot(coordinate_t& mouse_x, coordinate_t& mouse_y);
    ~Shoot();
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

class Drop: public InterfaceClientAction {
public:
    Drop();
    ~Drop();
    void action(ClientProtocol& protocol) override;
};

class Equip: public EquipCommon, public InterfaceClientAction {
public:
    Equip(EquipType& equip_type);
    ~Equip();
    void action(ClientProtocol& protocol) override;
};

class MousePosition: public MousePositionCommon, public InterfaceClientAction {
public:
    MousePosition(coordinate_t& mouse_x, coordinate_t& mouse_y);
    ~MousePosition();
    void action(ClientProtocol& protocol) override;
};

}  // namespace ClientSpace


#endif