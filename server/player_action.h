#ifndef PLAYER_ACTION_H
#define PLAYER_ACTION_H

#include <cstdint>
#include "common/player_types.h"
#include "game.h"

class PlayerAction
{
protected:
    uint16_t player_id;

public:
    PlayerAction(uint16_t player_id) : player_id(player_id) {}
    virtual ~PlayerAction() {}
    virtual void action(Game &game) = 0;
};

/*
        MOVEMENT ACTIONS
*/

class MoveRight : public PlayerAction
{
public:
    MoveRight(uint16_t player_id);
    ~MoveRight();
    void action(Game &game) override;
};

class MoveLeft : public PlayerAction
{
public:
    MoveLeft(uint16_t player_id);
    ~MoveLeft();
    void action(Game &game) override;
};

class MoveUp : public PlayerAction
{
public:
    MoveUp(uint16_t player_id);
    ~MoveUp();
    void action(Game &game) override;
};

class MoveDown : public PlayerAction
{
public:
    MoveDown(uint16_t player_id);
    ~MoveDown();
    void action(Game &game) override;
};

/*
        WEAPON ACTIONS
*/

class BuyWeapon : public PlayerAction
{
private:
    WeaponCode weapon_code;

public:
    BuyWeapon(uint16_t player_id, WeaponType weapon_type, WeaponCode weapon_code, ammo_t ammo_count);
    ~BuyWeapon();
    void action(Game &game) override;
};

class BuyAmmo : public PlayerAction
{
private:
    WeaponType weapon_type;
    ammo_t ammo_count;

public:
    BuyAmmo(uint16_t player_id, WeaponType weapon_type, ammo_t ammo_count);
    ~BuyAmmo();
    void action(Game &game) override;
};

class Reload : public PlayerAction
{
private:
    WeaponType ammo_type;

public:
    Reload(uint16_t player_id, WeaponType weapon_type);
    ~Reload();
    void action(Game &game) override;
};

class Shoot : public PlayerAction
{
private:
    WeaponType ammo_type;
    ammo_t ammo_count;

public:
    Shoot(uint16_t player_id);
    ~Shoot();
    void action(Game &game) override;
};

class DropWeapon : public PlayerAction
{
private:
    WeaponType weapon_type;

public:
    DropWeapon(uint16_t player_id, WeaponType weapon_type);
    ~DropWeapon();
    void action(Game &game) override;
};

class DropBomb : public PlayerAction
{
public:
    DropBomb(uint16_t player_id);
    ~DropBomb();
    void action(Game &game) override;
};

class

#endif // !PLAYER_ACTION_H
