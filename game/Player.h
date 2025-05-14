#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_
//  "Copyright 2025 Yaco Santamarina"
// #include "Equipement.h"
#include "Type.h"
#include "Physics.h"
#include <utility>
class Player {
public:
  enum Team { Terrorist, CounterTerrorist };
  Player(int _id ,std::string&&_nick_name, Vector2&& _position, Team team)
      : id(_id), nick_name(std::move(_nick_name)), position(std::move(_position)), health(100),current_team(team) , points(0){}

  void move(Vector2&& new_position);
  TypesStates::player_state_t player_info();
  /*
  void get_damage(int damage);
  void change_weapon_equiped();
  void fire_weapon_equiped();
  */
  private:
  int id;
  std::string nick_name;
  Vector2 position;
  // Equiment equipement;
  int health;
  Team current_team;
  int points;
};

#endif // GAME_PLAYER_H_
