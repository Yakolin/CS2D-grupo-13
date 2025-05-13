#ifndef PLAYER_ACTION_H
#define PLAYER_ACTION_H

#include <cstdint>
#include "common/player_types.h"
#include "game.h"

class PlayerAction
{
protected:
    std::uint16_t player_id;

public:
    PlayerAction(std::uint16_t player_id) : player_id(player_id) {}
    virtual ~PlayerAction() {}
    virtual void action(Game &game) = 0;
};

/*
        MOVEMENT ACTIONS
*/

class MoveRight : public PlayerAction
{
public:
    MoveRight(std::uint16_t player_id);
    ~MoveRight();
    void action(Game &game) override;
};

class MoveLeft : public PlayerAction
{
public:
    MoveLeft(std::uint16_t player_id);
    ~MoveLeft();
    void action(Game &game) override;
};

class MoveUp : public PlayerAction
{
public:
    MoveUp(std::uint16_t player_id);
    ~MoveUp();
    void action(Game &game) override;
};

class MoveDown : public PlayerAction
{
public:
    MoveDown(std::uint16_t player_id);
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
    BuyWeapon(std::uint16_t player_id, WeaponCode weapon_code); // considerando que el arma viene con municion por default
    ~BuyWeapon();
    void action(Game &game) override;
};

class BuyAmmo : public PlayerAction
{
private:
    WeaponType weapon_type;
    ammo_t ammo_count;

public:
    BuyAmmo(std::uint16_t player_id, WeaponType weapon_type, ammo_t ammo_count);
    ~BuyAmmo();
    void action(Game &game) override;
};

class Reload : public PlayerAction
{
private:
    WeaponType ammo_type;

public:
    Reload(std::uint16_t player_id, WeaponType weapon_type);
    ~Reload();
    void action(Game &game) override;
};

class Shoot : public PlayerAction
{
private:
    WeaponType weapon_type;
    ammo_t ammo_count;

public:
    Shoot(std::uint16_t player_id, WeaponType weapon_type, ammo_t ammo_count);
    ~Shoot();
    void action(Game &game) override;
};

class DropWeapon : public PlayerAction
{
private:
    WeaponType weapon_type;

public:
    DropWeapon(std::uint16_t player_id, WeaponType weapon_type);
    ~DropWeapon();
    void action(Game &game) override;
};

/*
        BOMB ACTIONS
*/

class PlantBomb : public PlayerAction
{
public:
    PlantBomb(std::uint16_t player_id);
    ~PlantBomb();
    void action(Game &game) override;
};

class DropBomb : public PlayerAction
{
public:
    DropBomb(std::uint16_t player_id);
    ~DropBomb();
    void action(Game &game) override;
};

class DefuseBomb : public PlayerAction
{
public:
    DefuseBomb(std::uint16_t player_id);
    ~DefuseBomb();
    void action(Game &game) override;
};

#endif // !PLAYER_ACTION_H
