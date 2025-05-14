#ifndef PLAYER_ACTION_H
#define PLAYER_ACTION_H

#include "../common/player_types.h"
#include "game.h"
#include <cstdint>

class PlayerAction {
protected:
  player_id_t player_id;

public:
  PlayerAction(player_id_t player_id) : player_id(player_id) {}
  virtual ~PlayerAction() {}
  virtual void action(InterfaceGame &game) = 0;
};

/*
        MOVEMENT ACTIONS
*/

class Move : public PlayerAction {
private:
  MoveType move_type;

public:
  Move(player_id_t player_id, MoveType move_type);
  ~Move();
  void action(InterfaceGame &game) override;
};

/*
        WEAPON ACTIONS
*/

class BuyWeapon : public PlayerAction {
private:
  WeaponCode weapon_code;

public:
  BuyWeapon(player_id_t player_id,
            WeaponCode weapon_code); // considerando que el arma viene con
                                     // municion por default
  ~BuyWeapon();
  void action(InterfaceGame &game) override;
};

class BuyAmmo : public PlayerAction {
private:
  WeaponType weapon_type;
  ammo_t ammo_count;

public:
  BuyAmmo(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count);
  ~BuyAmmo();
  void action(InterfaceGame &game) override;
};

class Reload : public PlayerAction {
private:
  WeaponType weapon_type;

public:
  Reload(player_id_t player_id, WeaponType weapon_type);
  ~Reload();
  void action(InterfaceGame &game) override;
};

class Shoot : public PlayerAction {
private:
  WeaponType weapon_type;
  ammo_t ammo_count;

public:
  Shoot(player_id_t player_id, WeaponType weapon_type, ammo_t ammo_count);
  ~Shoot();
  void action(InterfaceGame &game) override;
};

class DropWeapon : public PlayerAction {
private:
  WeaponType weapon_type;

public:
  DropWeapon(player_id_t player_id, WeaponType weapon_type);
  ~DropWeapon();
  void action(InterfaceGame &game) override;
};

/*
        BOMB ACTIONS
*/

class PlantBomb : public PlayerAction {
public:
  PlantBomb(player_id_t player_id);
  ~PlantBomb();
  void action(InterfaceGame &game) override;
};

class DropBomb : public PlayerAction {
public:
  DropBomb(player_id_t player_id);
  ~DropBomb();
  void action(InterfaceGame &game) override;
};

class DefuseBomb : public PlayerAction {
public:
  DefuseBomb(player_id_t player_id);
  ~DefuseBomb();
  void action(InterfaceGame &game) override;
};

#endif // !PLAYER_ACTION_H
